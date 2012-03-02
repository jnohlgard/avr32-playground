/**
 * \file IMU.cpp
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
 * \file IMU.cpp
 *
 * \section Description
 * \brief Implementation of Arduino library for interfacing with inertial measurement units (IMU)
 *
 * \section History
 * \date 1 March 2012 - First version
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

