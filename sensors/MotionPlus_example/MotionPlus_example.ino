/**
 * \file MotionPlus_example.ino
 * \author Joakim Gebart <joakim.gebart@jge.se>
 * \date 1 March 2012
 *
 * \brief Usage example for connecting Arduino to a Wii MotionPlus for use as an IMU.
 *
 * \section License
 * The author has placed this work in the Public Domain, thereby relinquishing
 * all copyrights. Everyone is free to use, modify, republish, sell or give away
 * this work without prior consent from anybody.
 */

#include <Wire.h>
#include <Wii.h>

#define USE_NUNCHUK true ///< Whether a nunchuk is connected
#define SERIAL_RATE 115200 ///< Serial port baudrate

using IMU::WiiMotionPlus;
WiiMotionPlus wmp(Wire, WiiMotionPlus::kDefaultMotionPlusPort, WiiMotionPlus::kDefaultExtensionPort, USE_NUNCHUK);


void setup()
{
    Serial.begin(SERIAL_RATE);
    Wire.begin();
    Serial.println("Starting...");
    wmp.init();
}

void loop()
{
    //~ Serial.println("Reading a measurement from IMU");
    // First time will update gyro
    wmp.measure();
    delay(5); // wait a few milliseconds before next measure, this should be tuned to the speed of the ADC in the MotionPlus/Nunchuk.
    // If we wait too short a time we will only get gyro reports (this is what happened to me, at least)
    // Second read will update accelerometer
    wmp.measure();
    Serial.print("a:\t");
    Serial.print(wmp.getAccelerometerX());
    Serial.print("\t");
    Serial.print(wmp.getAccelerometerY());
    Serial.print("\t");
    Serial.print(wmp.getAccelerometerZ());
    Serial.print("\tw:\t");
    Serial.print(wmp.getGyroX());
    Serial.print("\t");
    Serial.print(wmp.getGyroY());
    Serial.print("\t");
    Serial.print(wmp.getGyroZ());
    Serial.println("");
    delay(100);
}
