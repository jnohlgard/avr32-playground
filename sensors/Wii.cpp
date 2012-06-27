#include "Wii.hpp"
/**
 * \file Wii.cpp
 * \author Copyright (C) 2012 Joakim Gebart <joakim.gebart@jge.se>
 *
 * Arduino Sensors library - provides a unified interface towards sensors.
 *
 * \section License
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file Wii.cpp
 * \section Description
 *
 * \brief Arduino library for interfacing with Wii MotionPlus.
 *
 * Wii MotionPlus and Nunchuk combined into a 6DOF IMU connected to an Arduino
 * for passing on to a PC through the Arduino's USB serial port.
 *
 * \section History
 * \date 27 June 2012 - Ported Arduino sensors library to AVR32.
 * \date 1 March 2012 - Rewrote from scratch and made a separate library.
 * \date 30 october 2010 - First version
 */
#include "conf_system.h"
#include "system/system.h"

#define ENABLE_DEBUG 1

#ifdef NDEBUG
    #define ENABLE_DEBUG 0
#endif

#ifndef ENABLE_DEBUG
    #define ENABLE_DEBUG 0
#endif

#if ENABLE_DEBUG
    #ifndef DEBUG_IMU_PORT
        #define DEBUG_IMU_PORT gout
    #endif
#else
    #undef DEBUG_IMU_PORT
#endif
#ifdef DEBUG_IMU_PORT
    // write debug messages to serial port (or other Stream-like object)
    #define DEBUGPRINT(msg) DEBUG_IMU_PORT.print(msg)
    #define DEBUGPRINTLN(msg) DEBUG_IMU_PORT.print(msg).print("\n")
    #define DEBUGPRINTHEX(msg) DEBUG_IMU_PORT.print(msg)
#else
    // don't print debug messages
    #define DEBUGPRINT(msg)
    #define DEBUGPRINTLN(msg)
    #define DEBUGPRINTHEX(msg)
#endif

#define WII_INIT_DELAY 100

namespace IMU {
    WiiBase::WiiBase()
    {
    }

    WiiMotionPlus::WiiMotionPlus(twi_master_t twi_, uint8_t wmp_address_,
        uint8_t extension_address_, bool use_nunchuk_) :
        twi(twi_),
        wmp_address(wmp_address_),
        extension_address(extension_address_),
        use_nunchuk(use_nunchuk_)
    {
    }

    void WiiMotionPlus::init()
    {
        DEBUGPRINT("Initializing Wii MotionPlus...");
        fb->flush();
        twi_package_t pkg;
        uint8_t cmd;
        cmd = kCommandInitializeExtension;
        pkg.addr[0] = kAddressInitialize;
        pkg.addr_length = sizeof(uint8_t);
        pkg.chip = wmp_address;
        pkg.buffer = (void*)(&cmd);
        pkg.length = sizeof(cmd);
        //~ uint32_t status = twi_master_write_ex(twi, &pkg);
        //~ DEBUGPRINTLN(status);
        fb->flush();
        while (twi_master_write(twi, &pkg) != TWI_SUCCESS);
        DEBUGPRINTLN(" done.");
        fb->flush();
        //~ delay(WII_INIT_DELAY); // FIXME: Is delay neccessary?

        DEBUGPRINT("Set MotionPlus mode: ");
        fb->flush();
        pkg.addr[0] = kAddressMotionPlusMode;
        pkg.addr_length = sizeof(uint8_t);
        pkg.chip = wmp_address;
        pkg.buffer = (void*)(&cmd);
        pkg.length = sizeof(cmd);
        if (use_nunchuk)
        {
            DEBUGPRINT("Nunchuk+WMP combined... ");
            cmd = kMotionPlusModeNunchukCombined;
        }
        else
        {
            DEBUGPRINT("MotionPlus only... ");
            cmd = kMotionPlusModeMotionPlus;
        }
        fb->flush();
        while (twi_master_write(twi, &pkg) != TWI_SUCCESS);
        // After this WMP has changed address to 0x52
        DEBUGPRINTLN(" done.");
        fb->flush();
        //~ delay(WII_INIT_DELAY); // FIXME: Is delay neccessary?

        DEBUGPRINT("Requesting extension identifier...");
        fb->flush();
        pkg.addr[0] = kAddressIdentification;
        pkg.addr_length = sizeof(uint8_t);
        pkg.chip = extension_address;
        uint64_t extension_id = 0;
        pkg.buffer = (void*)(&extension_id);
        pkg.length = 6; // Extension ids are 6 bytes long
        // Perform a multi-byte read access then check the result.
        while (twi_master_read(twi, &pkg) != TWI_SUCCESS);
        DEBUGPRINTLN(" done.");
        fb->flush();
        //~ delay(WII_INIT_DELAY); // FIXME: Is delay neccessary?

        // Read extension ID
        //~ twi.requestFrom(extension_address, (uint8_t) 6);
        DEBUGPRINT("Extension ID: ");
        fb->flush();
        DEBUGPRINTLN((uint32_t)(extension_id>>16));
        fb->flush();
        //~ for (uint8_t i = 0; i < 6; ++i)
        //~ {
            //~ buf[i] = twi.read();
            //~ DEBUGPRINTHEX(buf[i]);
            //~ DEBUGPRINT(" ");
        //~ }
        //~ DEBUGPRINTLN("");
        /*
         * From http://wiibrew.org/wiki/Wiimote/Extension_Controllers#The_New_Way
         * Extension IDs: (not a complete list)
         *
         * 0000 A420 0000   Nunchuk
         * 0000 A420 0405   Activated Wii Motion Plus
         * 0000 A420 0505   Activated Wii Motion Plus in Nunchuk passthrough mode
         * 0000 A420 0705   Activated Wii Motion Plus in Classic Controller passthrough mode
         */
        //~ DEBUGPRINTLN("done.");

        DEBUGPRINT("Setting read address...");
        cmd = kAddressReport;
        pkg.addr_length = 0;
        pkg.chip = extension_address;
        pkg.buffer = (void*)(&cmd);
        pkg.length = sizeof(cmd);
        while (twi_master_write(twi, &pkg) != TWI_SUCCESS);
        //~ twi.beginTransmission(extension_address);
        //~ twi.write(kAddressReport);
        //~ twi.endTransmission();
        DEBUGPRINTLN(" done.");
        DEBUGPRINTLN("MotionPlus initialization complete.");
        fb->flush();
    }

    bool WiiMotionPlus::hasGyro()
    {
        // MotionPlus has a 3-axis gyro
        return true;
    }

    bool WiiMotionPlus::hasAccelerometer()
    {
        // Nunchuk has a 3-axis accelerometer
        return use_nunchuk;
    }

    void WiiMotionPlus::measure()
    {
        //~ DEBUGPRINTLN("------ BEGIN WiiMotionPlus::measure() ------");

        twi_package_t pkg;
        uint8_t cmd;
        cmd = kCommandRequestReport;
        //~ pkg.addr[0] = kAddressReport;
        //~ pkg.addr_length = sizeof(uint8_t);
        pkg.addr_length = 0;
        pkg.chip = extension_address;
        pkg.buffer = (void*)(&cmd);
        pkg.length = sizeof(cmd);
        while (twi_master_write(twi, &pkg) != TWI_SUCCESS);
        pkg.buffer = (void*)(&buf[0]);
        pkg.length = sizeof(buf);
        pkg.addr_length = 0;
        // Perform a multi-byte read access then check the result.
        while (twi_master_read(twi, &pkg) != TWI_SUCCESS);

        // Request report (tell WMP to read sensors)
        //~ twi.beginTransmission(extension_address);
        //~ twi.write(kCommandRequestReport);
        //~ twi.endTransmission();

        // Read report
        //~ twi.requestFrom(extension_address, (uint8_t) 6);
        //~ DEBUGPRINT("Data: ");
        //~ for (int i=0;i<6;i++)
        //~ {
            //~ buf[i]=twi.read();
            //~ DEBUGPRINTHEX(buf[i]);
            //~ DEBUGPRINT(" ");
        //~ }
        //~ DEBUGPRINTLN("");

        // Parse report
        parseSensorData();

        //~ DEBUGPRINTLN("------ END WiiMotionPlus::measure() ------");
    }

    /// Parse data from Wii MotionPlus
    /**
     * The data format is described at WiiBrew.
     * @see http://wiibrew.org/wiki/Wiimote/Extension_Controllers#Data_Format_.28Wii_Motion_Plus.29
     * @see http://www.assembla.com/wiki/show/alicewiimotionplus/Using_extensions_via_the_Motion_Plus
     * @see http://www.assembla.com/wiki/show/alicewiimotionplus/Slow_and_fast_modes
     */
    void WiiMotionPlus::parseSensorData()
    {
        // Bit 0 in buf[4] tells us whether there is an extension connected to the WMP
        // Bits 0,1 in buf[5] tells us whether the packet contains extension data or WMP data
        // currently 0x02 means WMP data, 0x00 means nunchuk data, see Wii.h
        if ((buf[kExtensionIDByte] & kExtensionIDBitmask) == kExtensionIDMotionPlus)
        {
            //~ DEBUGPRINTLN("Gyro data");
            // WMP data
            /// \bug doesn't handle the slow bit on gyro packets.
            /// \todo Right handed system
            wx = static_cast<uint16_t>((buf[3] & 0xFC) << 6) | buf[0];
            wy = static_cast<uint16_t>((buf[4] & 0xFC) << 6) | buf[1];
            wz = static_cast<uint16_t>((buf[5] & 0xFC) << 6) | buf[2];
            /// \see http://invensense.com/mems/gyro/idg650.html
            // (IDG-600 is similar to IDG-650)
            // The ADC value in slow mode is 4.5x the value in fast mode, hence
            // we should multiply the read value by 4.5 to get the absolute
            // value in fast mode.
            // Parse slow bit from packet
            wx_scale = (((buf[4] & 0x02) >> 1) ? gyro_slow_scale : gyro_fast_scale);
            wy_scale = (((buf[3] & 0x01) >> 0) ? gyro_slow_scale : gyro_fast_scale);
            wz_scale = (((buf[3] & 0x02) >> 1) ? gyro_slow_scale : gyro_fast_scale);
        }
        else if ((buf[kExtensionConnectedByte] & kExtensionConnectedBitmask) &&
            ((buf[kExtensionIDByte] & kExtensionIDBitmask) == kExtensionIDNunchuk))
        {
            //~ DEBUGPRINTLN("Accelerometer data");
            // Nunchuk data
            /// \todo Right handed system
            // The signs and order of these axes are the same as on WiiBrew
            ax = static_cast<uint16_t>(buf[2] << 2) | ((buf[5] >> 3) & 0x02);
            ay = static_cast<uint16_t>(buf[3] << 2) | ((buf[5] >> 4) & 0x02);
            az = static_cast<uint16_t>((buf[4] & 0xFE) << 2) | ((buf[5] >> 5) & 0x06);
        }
        // else ???
    }

    AccelerometerValue WiiMotionPlus::getAccelerometerX()
    {
        //~ DEBUGPRINTLN("Bajs");
        return ax;
    }

    AccelerometerValue WiiMotionPlus::getAccelerometerY()
    {
        return ay;
    }

    AccelerometerValue WiiMotionPlus::getAccelerometerZ()
    {
        return az;
    }

    GyroValue WiiMotionPlus::getGyroX()
    {
        return wx;
    }

    GyroValue WiiMotionPlus::getGyroY()
    {
        return wy;
    }

    GyroValue WiiMotionPlus::getGyroZ()
    {
        return wz;
    }

    GyroValue WiiMotionPlus::getGyroScaleX()
    {
        return wx_scale;
    }

    GyroValue WiiMotionPlus::getGyroScaleY()
    {
        return wy_scale;
    }

    GyroValue WiiMotionPlus::getGyroScaleZ()
    {
        return wz_scale;
    }
}
