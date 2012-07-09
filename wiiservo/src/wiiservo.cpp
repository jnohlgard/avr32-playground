#include "board.h"
#include "conf_system.h"
#include "system/system.h"
#include "sensors/Wii.hpp"
#include "servo/servo.h"
//~ #include "system/system_init.h"
//~ #include "system/streams.hpp"
//~ #include "system/framebuffer.hpp"
extern "C" {
#include "stubs/_isatty.h"
#include <drivers/gpio/gpio.h>
#include <drivers/tc/tc.h>
}
//~ #include <cstring>
//~ #include <cstdio>
//~ #include "stubs/newdel.hpp"
#include "Framebuffer/Scope.hpp"

#define USE_NUNCHUK true ///< Whether a nunchuk is connected

using IMU::WiiMotionPlus;
WiiMotionPlus wmp(CONF_SYSTEM_TWI, WiiMotionPlus::kDefaultMotionPlusPort, WiiMotionPlus::kDefaultExtensionPort, USE_NUNCHUK);

bool backwards = true;

void loop()
{
    static Scope wiiplot(*fb, 0, 0, 128, 64);
    //~ fb->clear();
    fb->clearRectangle(0, 0, 128, 8);
    wmp.measure(); // Accelerometer and gyro are updated in lockstep
    wmp.measure();
    wiiplot.put(wmp.getAccelerometerX() * wmp.getAccelerometerScaleX());
    g_servos[0].value = wmp.getAccelerometerX() * 29;
    //~ if (backwards)
    //~ {
        //~ --(g_servos[0].value);
        //~ if (g_servos[0].value <= 120)
        //~ {
            //~ backwards = false;
        //~ }
    //~ }
    //~ else
    //~ {
        //~ ++(g_servos[0].value);
        //~ if (g_servos[0].value >= 1000)
        //~ {
            //~ backwards = true;
        //~ }
    //~ }
    gout.setPos(0, 0);
    gout << g_servos[0].value;
    //~ gout << "A: " << wmp.getAccelerometerX() << ", " << wmp.getAccelerometerY() << ", " << wmp.getAccelerometerZ() << "\n";
    fb->flush();
    //~ gout << "W: " << wmp.getGyroX() << ", " << wmp.getGyroY() << ", " << wmp.getGyroZ() << "\n";
    //~ gout << "min_y: " << static_cast<uint32_t>(wiiplot.min_y) << " max_y: " << static_cast<uint32_t>(wiiplot.max_y) << "\n";
    //~ gout << "scale_y: " << static_cast<uint32_t>(wiiplot.scale_y * 1000000.f) << "\n";
    //~ if (g_current_servo == 0)
    //~ {
        //~ gout << static_cast<uint16_t>(g_current_servo) << ": " << (uint32_t)tc_read_ra(SERVO_TC, SERVO_TC_CHANNEL)
            //~ << " - " << (uint32_t)tc_read_rc(SERVO_TC, SERVO_TC_CHANNEL)
            //~ << " (" << (uint32_t)tc_read_tc(SERVO_TC, SERVO_TC_CHANNEL) << ")";
        //~ gout.newline();
        //~ fb->flush();
    //~ }
    //~ for (;;);

    //~ for(int u = 0; u < 1000000; ++u)
    //~ {
        //~ asm volatile ("nop\n");
    //~ }
}

int main(int, char**)
{
    // Initialize hardware
    system_init();

    wmp.init();
    fb->flush();

    gout << "Initializing servo timer/counter\n";
    fb->flush();
    initServoTimer();
    gout << "Max servo value: " << g_servo_max_value << "\n";
    fb->flush();

    //~ unsigned char str[] = "Hej!\nblahblah testar\n1234567890123456789012345678901234567890\n\n12345678\n123456789";
    //~ gout->print(sizeof(str), &str[0]);
    //~ fb->clear(0xaa);
    //~ fb->line(0, 10, 100, 63, 0);
    //~ fb->flush();

    gout << "Enabling servo #0\n";
	gpio_configure_pin(AVR32_PIN_PB00, GPIO_DIR_OUTPUT);
    g_servos[0].pin = AVR32_PIN_PB00;
    g_servos[0].value = 15000;
    g_servos[0].enabled = 1;
    fb->flush();

    for (;;) // never exit
    {
        loop();
    }
    return 0;
}
