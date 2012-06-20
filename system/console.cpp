#include "system/console.h"
#include "system/streams.hpp"
#include "system/framebuffer.hpp"
#include "board.h"
#include "conf_system.h"
//~ #include <drivers/intc/intc.h>
//~ #include <drivers/tc/tc.h>
#include <services/clock/sysclk.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONF_SYSTEM_OLED_CONSOLE

#include CONF_SYSTEM_OLED_FONT_FILE

void initOLEDConsole(void)
{
    gout.bind(fb);
    gout.setFont(CONF_SYSTEM_OLED_FONT);
    gout << "OLED console initialized.\n";
    #ifdef CONF_SYSTEM_OLED_FONT_MONOSPACE
    gout->setMonospace(CONF_SYSTEM_OLED_FONT_MONOSPACE);
    #endif
    gout.flush();
}
#endif // CONF_SYSTEM_OLED_CONSOLE

#ifdef CONF_SYSTEM_CONSOLE
void initConsole(void)
{
    #ifdef CONF_SYSTEM_OLED_CONSOLE
        #ifndef CONF_SYSTEM_OLED
            #error CONF_SYSTEM_OLED_CONSOLE requires CONF_SYSTEM_OLED
        #endif
        initOLEDConsole();
    #endif // CONF_SYSTEM_OLED_CONSOLE
    #ifdef CONF_SYSTEM_SERIAL_CONSOLE
        initSerialConsole();
    #endif // CONF_SYSTEM_SERIAL_CONSOLE
}
#endif // CONF_SYSTEM_CONSOLE

#ifdef CONF_SYSTEM_SERIAL_CONSOLE

#include <drivers/usart/usart.h>

void initSerialConsole(void)
{
    // USART options.
    usart_options_t usart_options;
    usart_options.baudrate     = CONF_SYSTEM_SERIAL_CONSOLE_BAUDRATE;
    usart_options.charlength   = CONF_SYSTEM_SERIAL_CONSOLE_CHARLENGTH;
    usart_options.paritytype   = CONF_SYSTEM_SERIAL_CONSOLE_PARITY;
    usart_options.stopbits     = CONF_SYSTEM_SERIAL_CONSOLE_STOPBITS;
    usart_options.channelmode  = CONF_SYSTEM_SERIAL_CONSOLE_CHANNELMODE;

    // Initialize USART in RS232 mode.
    sysclk_enable_peripheral_clock(USART);
    usart_init_rs232(USART, &usart_options, sysclk_get_peripheral_bus_hz(USART));

    // Disable all interrupts.
    //~ cpu_irq_disable();

    //~ INTC_register_interrupt(&usart_int_handler, USART_IRQ,
        //~ USART_IRQ_PRIORITY);

    // Enable all interrupts.
    //~ cpu_irq_enable();

    //~ USART->ier = AVR32_USART_IER_RXRDY_MASK;
    gout.print("Serial console initialized.\r\n");
    usart_write_line(USART, "Serial console initialized.\r\n");
}

#endif // CONF_SYSTEM_SERIAL_CONSOLE

#ifdef __cplusplus
}
#endif
