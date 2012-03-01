#ifndef _IMU_WII_H_
#define _IMU_WII_H_
/**
 * \file Wii.h
 *
 * \author Joakim Gebart <joakim.gebart@jge.se>
 * \date 29 february 2012
 *
 * \brief Arduino library for interfacing with Wii MotionPlus.
 *
 * Wii MotionPlus and Nunchuk combined into a 6DOF IMU connected to an Arduino
 * for passing on to a PC through the Arduino's USB serial port.
 *
 * Some of the initialization code is based on code found on the Arduino forums
 *
 * 31 october 2010 - First version
 */

#include <stdint.h>
#include <Wire.h>
#include "IMU.h"

namespace IMU {

    /// \class IMU::WiiBase
    /// \brief Base class for Wii Nunchuk and MotionPlus used as an IMU.
    /// \note the implementation of these classes requires several reverse-engineered magic incantations.
    /// \see http://wiibrew.org/wiki/Wiimote/Extension_Controllers
    class WiiBase : public IMUInterface
    {
        public:
            /// Constructor
            WiiBase();
            /// Default i2c address for normal Wii extensions
            static const uint8_t kDefaultExtensionPort       = 0x52;
            /// Default i2c address for Wii MotionPlus
            static const uint8_t kDefaultMotionPlusPort      = 0x53;

        protected:
            // Magic numbers reverse engineered by wiibrew.org users
            /// Send this to tell the extension controller to transmit an extension report
            static const uint8_t kCommandRequestReport       = 0x00;
            /// Send this to initialize the extension controller
            static const uint8_t kCommandInitializeExtension = 0x55;
            /// Send this to activate the extension controller
            static const uint8_t kCommandActivateExtension   = 0x00;
            /// Address of extension identification register
            static const uint8_t kAddressIdentification      = 0xFA;
            /// Address of initialization register
            static const uint8_t kAddressInitialize          = 0xF0;
            /// Address to write extension activation command
            static const uint8_t kAddressActivateExtension   = 0xFB;
            /// Address of extension reports
            static const uint8_t kAddressReport              = 0x08;

        private:
    };

    class WiiNunchuk : public WiiBase
    {
    };

    class WiiMotionPlus : public WiiBase
    {
        public:
            /// Default constructor
            WiiMotionPlus();
            /// Real constructor
            WiiMotionPlus(TwoWire&, uint8_t, uint8_t, bool = false);
            /// Initialize MotionPlus over i2c
            virtual void init();
            virtual void measure();

            virtual bool hasGyro();
            virtual bool hasAccelerometer();

            virtual GyroValue getGyroX();
            virtual GyroValue getGyroY();
            virtual GyroValue getGyroZ();
            virtual GyroValue getGyroScaleX();
            virtual GyroValue getGyroScaleY();
            virtual GyroValue getGyroScaleZ();

            virtual AccelerometerValue getAccelerometerX();
            virtual AccelerometerValue getAccelerometerY();
            virtual AccelerometerValue getAccelerometerZ();

        protected:

        private:
            void parseSensorData();
            TwoWire& twi;
            uint8_t wmp_address;
            uint8_t extension_address;
            bool use_nunchuk;
            uint8_t buf[6]; ///< i2c receive buffer

            AccelerometerValue ax, ay, az;
            GyroValue wx, wy, wz;
            GyroValue wx_scale, wy_scale, wz_scale;

            // Magic numbers reverse engineered by wiibrew.org users
            /// Address of mode-switch register for MotionPlus
            static const uint8_t kAddressMotionPlusMode         = 0xFE;
            /// MotionPlus only mode
            static const uint8_t kMotionPlusModeMotionPlus      = 0x04;
            /// Nunchuk + Motionplus combined mode
            static const uint8_t kMotionPlusModeNunchukCombined = 0x05;
            /// Classic controller (or music game controller) + Motionplus combined mode, pretty useless here but included for completeness
            static const uint8_t kMotionPlusModeClassicCombined = 0x07;

            /// Byte number for Extension Connected bit (inside extension report packet)
            static const uint8_t kExtensionConnectedByte        = 4;
            /// Bitmask for Extension Connected bit
            static const uint8_t kExtensionConnectedBitmask     = 0x01;
            /// Byte number for Extension ID bits (inside extension report packet)
            static const uint8_t kExtensionIDByte               = 5;
            /// Bitmask for Extension ID bits
            static const uint8_t kExtensionIDBitmask            = 0x03;
            /// Extension ID == Nunchuk
            static const uint8_t kExtensionIDNunchuk            = 0x00;
            /// Extension ID == MotionPlus
            static const uint8_t kExtensionIDMotionPlus         = 0x02;

            // The scale factors below are needed because the gyros have two
            // analog outputs, one at 440 deg/s upper limit, one at 2000 deg/s.
            // To convert raw value from fast to slow we multiply the fast value
            // by 4.5 but to avoid floating point we multiply slow values by 2
            // and fast values by 9.
            // 32 bit int is slow on AVR, but not as slow as 32 bit softfloat.
            /// Scale factor for fast gyro mode
            static const GyroValue gyro_fast_scale = 9;
            /// Scale factor for slow gyro mode
            static const GyroValue gyro_slow_scale = 2;

    };
}
#endif
