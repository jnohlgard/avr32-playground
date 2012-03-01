/**
 * \file IMU.cpp
 *
 * \author Joakim Gebart <joakim.gebart@jge.se>
 * \date 1 March 2012
 *
 * \brief Implementation of Arduino library for interfacing with inertial measurement units (IMU)
 *
 */

#include "IMU.h"

namespace IMU {
    GyroValue IMUInterface::getGyroX()
    {
        return 0;
    }
    GyroValue IMUInterface::getGyroY()
    {
        return 0;
    }
    GyroValue IMUInterface::getGyroZ()
    {
        return 0;
    }
    GyroValue IMUInterface::getGyroScaleX()
    {
        return 1;
    }
    GyroValue IMUInterface::getGyroScaleY()
    {
        return 1;
    }
    GyroValue IMUInterface::getGyroScaleZ()
    {
        return 1;
    }
    AccelerometerValue IMUInterface::getAccelerometerX()
    {
        return 0;
    }
    AccelerometerValue IMUInterface::getAccelerometerY()
    {
        return 0;
    }
    AccelerometerValue IMUInterface::getAccelerometerZ()
    {
        return 0;
    }
    AccelerometerValue IMUInterface::getAccelerometerScaleX()
    {
        return 1;
    }
    AccelerometerValue IMUInterface::getAccelerometerScaleY()
    {
        return 1;
    }
    AccelerometerValue IMUInterface::getAccelerometerScaleZ()
    {
        return 1;
    }
}

