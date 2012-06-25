#ifndef _SENSORS_IMU_H_
#define _SENSORS_IMU_H_
/**
 * \file IMU.h
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
 * \file IMU.h
 *
 * \section Description
 * \brief Arduino library for interfacing with inertial measurement units (IMU)
 *
 * \section History
 * \date 1 March 2012 - First version
 *
 */

#include <stdint.h>


namespace IMU {

    /// Data type for raw gyro readings
    typedef uint16_t GyroValue;

    /// Data type for raw accelerometer readings
    typedef uint16_t AccelerometerValue;

    /**
     * \class IMUInterface
     *
     * \brief Unified interface for using IMUs in Arduino code.
     */
    class IMUInterface
    {
        public:
            /**
             * \brief Initialize the sensor(s)
             *
             * This would typically turn on the sensor and prepare the hardware
             * so that we next can call measure() to trigger a measurement.
             *
             * init() should only contain code that needs to be run once, code
             * that must be run before each measurement should be placed in
             * measure().
             */
            virtual void init() = 0;

            /**
             * \brief Tell sensor unit to measure a new sample.
             *
             * This would typically trigger the sensor to do an A/D-conversion
             * (if the sensor is analog) and store the value in some private
             * variable.
             */
            virtual void measure() = 0;
            /**
             * \brief Does this IMU have a gyro attached?
             *
             * \return true if a gyro exists and is enabled on this sensor.
             */
            virtual bool hasGyro() = 0;

            /**
             * Does this IMU have an accelerometer attached?
             *
             * \return true if an accelerometer exists and is enabled on this sensor.
             */
            virtual bool hasAccelerometer() = 0;

            /**
             * \brief Read gyro \f$ \omega_{x,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the angular velocity along the X-axis of the last
             *         measurement.
             */
            virtual GyroValue getGyroX();

            /**
             * \brief Read gyro \f$ \omega_{y,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the angular velocity along the Y-axis of the last
             *         measurement.
             */
            virtual GyroValue getGyroY();

            /**
             * \brief Read gyro \f$ \omega_{z,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the angular velocity along the Z-axis of the last
             *         measurement.
             */
            virtual GyroValue getGyroZ();

            /**
             * \brief Read gyro scale factor \f$ K_{\omega_{x}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for angular velocity along the
             *         X-axis of the last measurement.
             */
            virtual GyroValue getGyroScaleX();

            /**
             * \brief Read gyro scale factor \f$ K_{\omega_{y}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for angular velocity along the
             *         Y-axis of the last measurement.
             */
            virtual GyroValue getGyroScaleY();

            /**
             * \brief Read gyro scale factor \f$ K_{\omega_{z}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for angular velocity along the
             *         Z-axis of the last measurement.
             */
            virtual GyroValue getGyroScaleZ();

            /**
             * \brief Read accelerometer \f$ a_{x,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the linear acceleration along the X-axis of the last
             *         measurement.
             */
            virtual AccelerometerValue getAccelerometerX();

            /**
             * \brief Read accelerometer \f$ a_{y,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the linear acceleration along the Y-axis of the last
             *         measurement.
             */
            virtual AccelerometerValue getAccelerometerY();

            /**
             * \brief Read accelerometer \f$ a_{z,raw} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note This will return the unfiltered raw value, filtering should
             *       be done by the user.
             *
             * \return the linear acceleration along the Z-axis of the last
             *         measurement.
             */
            virtual AccelerometerValue getAccelerometerZ();

            /**
             * \brief Read accelerometer scale factor \f$ K_{a_{x}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for linear acceleration along the
             *         X-axis of the last measurement.
             */
            virtual AccelerometerValue getAccelerometerScaleX();

            /**
             * \brief Read accelerometer scale factor \f$ K_{a_{y}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for linear acceleration along the
             *         Y-axis of the last measurement.
             */
            virtual AccelerometerValue getAccelerometerScaleY();

            /**
             * \brief Read accelerometer scale factor \f$ K_{a_{z}} \f$
             *
             * \note measure() must be explicitly called to actually read the
             *       hardware sensor
             *
             * \note The scale factor may change by every measurement.
             *
             * \return the sensor scale factor for linear acceleration along the
             *         Z-axis of the last measurement.
             */
            virtual AccelerometerValue getAccelerometerScaleZ();

        protected:
    };
}

#endif
