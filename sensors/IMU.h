#ifndef _IMU_IMU_H_
#define _IMU_IMU_H_
/**
 * \file IMU.h
 *
 * \author Joakim Gebart <joakim.gebart@jge.se>
 * \date 1 March 2012
 *
 * \brief Arduino library for interfacing with inertial measurement units (IMU)
 *
 */

#include <stdint.h>


namespace IMU {
    typedef uint32_t GyroValue;
    typedef uint16_t AccelerometerValue;
    class IMUInterface
    {
        public:
            /// Initialize the sensor(s)
            virtual void init() = 0;
            /// Tell sensor unit to measure a new sample
            virtual void measure() = 0;
            //~ /// Do we have data available?
            //~ virtual bool dataAvailable() = 0;
            /// Does this IMU have a gyro attached?
            virtual bool hasGyro() = 0;
            /// Does this IMU have an accelerometer attached?
            virtual bool hasAccelerometer() = 0;

            /// Read gyro \f$ \omega_{x,raw} \f$
            virtual GyroValue getGyroX();
            /// Read gyro \f$ \omega_{y,raw} \f$
            virtual GyroValue getGyroY();
            /// Read gyro \f$ \omega_{z,raw} \f$
            virtual GyroValue getGyroZ();
            /// Read gyro scale factor \f$ K_{\omega_{x}} \f$
            virtual GyroValue getGyroScaleX();
            /// Read gyro scale factor \f$ K_{\omega_{y}} \f$
            virtual GyroValue getGyroScaleY();
            /// Read gyro scale factor \f$ K_{\omega_{z}} \f$
            virtual GyroValue getGyroScaleZ();

            /// Read accelerometer \f$ a_{x,raw} \f$
            virtual AccelerometerValue getAccelerometerX();
            /// Read accelerometer \f$ a_{y,raw} \f$
            virtual AccelerometerValue getAccelerometerY();
            /// Read accelerometer \f$ a_{z,raw} \f$
            virtual AccelerometerValue getAccelerometerZ();
            /// Read accelerometer scale factor \f$ K_{a_{x}} \f$
            virtual AccelerometerValue getAccelerometerScaleX();
            /// Read accelerometer scale factor \f$ K_{a_{y}} \f$
            virtual AccelerometerValue getAccelerometerScaleY();
            /// Read accelerometer scale factor \f$ K_{a_{z}} \f$
            virtual AccelerometerValue getAccelerometerScaleZ();

        protected:
    };
}

#endif
