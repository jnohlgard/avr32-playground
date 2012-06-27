#ifndef CONF_SYSTEM_H_INCLUDED
#define CONF_SYSTEM_H_INCLUDED

//! \note TC module is used.
#define TICK_TC                 (&AVR32_TC)
//! \note TC Channel 0 is used.
#define TICK_TC_CHANNEL         0
//! \note IRQ0 line of channel 0 is used.
#define TICK_TC_IRQ             AVR32_TC_IRQ0
//! \note IRQ Group of TC module
#define TICK_TC_IRQ_GROUP       AVR32_TC_IRQ_GROUP
//! \note Interrupt priority 0 is used for TC.
#define TICK_TC_IRQ_PRIORITY    AVR32_INTC_INT0
//! \note LED0 is toggled on each timer tick.
#define TICK_TOGGLE_PIN         LED0_GPIO

#define TICK_RATE_HZ            100

#define USART_IRQ_PRIORITY      AVR32_INTC_INT1

// configure OLED framebuffer
#define CONF_SYSTEM_OLED
// Use tick timer
#define CONF_SYSTEM_TICK_TIMER
// Use console
#define CONF_SYSTEM_CONSOLE
// Serial console settings
#define CONF_SYSTEM_SERIAL_CONSOLE
#define CONF_SYSTEM_SERIAL_CONSOLE_BAUDRATE   57600
#define CONF_SYSTEM_SERIAL_CONSOLE_CHARLENGTH 8
#define CONF_SYSTEM_SERIAL_CONSOLE_PARITY     USART_NO_PARITY
#define CONF_SYSTEM_SERIAL_CONSOLE_STOPBITS   USART_1_STOPBIT
#define CONF_SYSTEM_SERIAL_CONSOLE_CHANNELMODE USART_NORMAL_CHMODE
// Use OLED console settings
#define CONF_SYSTEM_OLED_CONSOLE
//~ #define CONF_SYSTEM_OLED_FONT_FILE "Framebuffer/fonts/font3x5.h"
//~ #define CONF_SYSTEM_OLED_FONT      (Fonts::font3x5)
#define CONF_SYSTEM_OLED_FONT_FILE "Framebuffer/fonts/font5x8.h"
#define CONF_SYSTEM_OLED_FONT      (Fonts::font5x8)
#define CONF_SYSTEM_OLED_MONOSPACE 0

// Initialize TWI
#define CONF_SYSTEM_TWI         (&AVR32_TWI)
#define CONF_SYSTEM_TWI_SPEED   (50000)
#define CONF_SYSTEM_TWI_ADDR    (0x53)

#endif // CONF_SYSTEM_H_INCLUDED
