#include "board.h"
#include "conf_system.h"
#include "system/system.h"
//~ #include "system/system_init.h"
//~ #include "system/streams.hpp"
//~ #include "system/framebuffer.hpp"
extern "C" {
#include "stubs/_isatty.h"
}
//~ #include <cstring>
//~ #include <cstdio>
//~ #include "stubs/newdel.hpp"

#if 0
#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined(__ICCAVR32__)
__interrupt
#endif
static void usart_int_handler(void)
{
    int c;

    /*
     * In the code line below, the interrupt priority level does not need to
     * be explicitly masked as it is already because we are within the
     * interrupt handler.
     * The USART Rx interrupt flag is cleared by side effect when reading
     * the received character.
     * Waiting until the interrupt has actually been cleared is here useless
     * as the call to usart_write_char will take enough time for this before
     * the interrupt handler is left and the interrupt priority level is
     * unmasked by the CPU.
     */
    usart_read_char(USART, &c);
    unsigned char ch = c;

    // Print the received character to USART. This is a simple echo.
    usart_write_char(USART, ch);
    if (ch == '\r')
    {
        // Add LF to CR echo
        usart_write_char(USART, '\n');
    }
    gout.put(ch);
}
#endif

void loop()
{
    gout.newline();
    //~ gout->print(system_ticks);
    //~ gout->newline();
    gout << ":" << (int16_t)system_ticks << " = " << system_ticks << ";";
    //~ gout << system_ticks;
    //~ gout << (int16_t)13830;
    //~ gout.print(1, &i);
    //~ fb->text(0, 40, 1, &i, sizeof(Fonts::font3x5), Fonts::font3x5, 0);
    uout << "Hej: " << system_ticks;
    uout.newline();
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
