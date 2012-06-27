#include "board.h"
#include "conf_system.h"
#include "system/system.h"
#include "sensors/Wii.hpp"
//~ #include "system/system_init.h"
//~ #include "system/streams.hpp"
//~ #include "system/framebuffer.hpp"
extern "C" {
#include "stubs/_isatty.h"
}
//~ #include <cstring>
//~ #include <cstdio>
//~ #include "stubs/newdel.hpp"

#define USE_NUNCHUK true ///< Whether a nunchuk is connected

using IMU::WiiMotionPlus;
WiiMotionPlus wmp(CONF_SYSTEM_TWI, WiiMotionPlus::kDefaultMotionPlusPort, WiiMotionPlus::kDefaultExtensionPort, USE_NUNCHUK);

void loop()
{
    fb->flush();
    wmp.measure();
    gout << "A: " << wmp.getAccelerometerX() << ", " << wmp.getAccelerometerY() << ", " << wmp.getAccelerometerZ() << "\n";
    fb->flush();
    gout << "W: " << wmp.getGyroX() << ", " << wmp.getGyroY() << ", " << wmp.getGyroZ() << "\n";
    fb->flush();

    for(int u = 0; u < 1000000; ++u)
    {
        asm volatile ("nop\n");
    }
}

int main(int, char**)
{
    // Initialize hardware
    system_init();

    fb->flush();
    wmp.init();
    fb->flush();
    wmp.measure();
    gout << "A: " << wmp.getAccelerometerX() << ", " << wmp.getAccelerometerY() << ", " << wmp.getAccelerometerZ() << "\n";
    fb->flush();
    gout << "W: " << wmp.getGyroX() << ", " << wmp.getGyroY() << ", " << wmp.getGyroZ() << "\n";
    fb->flush();

    //~ unsigned char str[] = "Hej!\nblahblah testar\n1234567890123456789012345678901234567890\n\n12345678\n123456789";
    //~ gout->print(sizeof(str), &str[0]);
    //~ fb->clear(0xaa);
    //~ fb->line(0, 10, 100, 63, 0);
    //~ fb->flush();
    for (;;) // never exit
    {
        loop();
    }
    return 0;
}
