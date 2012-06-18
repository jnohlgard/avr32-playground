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

#endif // CONF_SYSTEM_H_INCLUDED
