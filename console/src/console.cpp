#include "board.h"
#include "conf_system.h"
extern "C" {
#include <drivers/intc/intc.h>
#include <drivers/usart/usart.h>
#include <drivers/tc/tc.h>
#include <services/clock/sysclk.h>
}
#include "Framebuffer/SSD1306.hpp"
#include "Framebuffer/FramebufferConsole.hpp"
#include "Framebuffer/fonts/tom_thumb.h"
extern "C" {
#include "stubs/_isatty.h"
}
//~ #include <cstring>
//~ #include <cstdio>
//~ #include "stubs/newdel.hpp"


typedef SSD1306Framebuffer FBDev;
//~ SSD1306Framebuffer oled(SSD1306_SPI, SSD1306_SPI_NPCS, SSD1306_GPIO_DC_PIN, SSD1306_GPIO_RST_PIN, 128, 64);
//~ Framebuffer* fb = &oled;
Framebuffer* fb;
FramebufferConsole* gout;

uint32_t system_ticks;

/**
 * \brief TC interrupt.
 *
 * The ISR handles RC compare interrupt and sets the update_timer flag to
 * update the timer value.
 */
#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
#pragma handler = EXAMPLE_TC_IRQ_GROUP, 1
__interrupt
#endif
static void tick_irq(void)
{
	// Increment the ms seconds counter
	system_ticks++;

	// Clear the interrupt flag. This is a side effect of reading the TC SR.
	tc_read_sr(TICK_TC, TICK_TC_CHANNEL);

	// specify that an interrupt has been raised
	//~ update_timer = true;
	// Toggle a GPIO pin (this pin is used as a regular GPIO pin).
	gpio_tgl_gpio_pin(TICK_TOGGLE_PIN);
}

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
    gout->print(1, &ch);
}

void initSystemTickTimer()
{
    system_ticks = 0;
    sysclk_enable_peripheral_clock(TICK_TC);

    // Disable all interrupts.
    cpu_irq_disable();

    // Register the RTC interrupt handler to the interrupt controller.
    INTC_register_interrupt(&tick_irq, TICK_TC_IRQ, TICK_TC_IRQ_PRIORITY);

    // Enable all interrupts.
    cpu_irq_enable();

    // Options for waveform generation.
    tc_waveform_opt_t waveform_opt;
    // Channel selection.
    waveform_opt.channel  = TICK_TC_CHANNEL;
    // Software trigger effect on TIOB.
    waveform_opt.bswtrg   = TC_EVT_EFFECT_NOOP;
    // External event effect on TIOB.
    waveform_opt.beevt    = TC_EVT_EFFECT_NOOP;
    // RC compare effect on TIOB.
    waveform_opt.bcpc     = TC_EVT_EFFECT_NOOP;
    // RB compare effect on TIOB.
    waveform_opt.bcpb     = TC_EVT_EFFECT_NOOP;
    // Software trigger effect on TIOA.
    waveform_opt.aswtrg   = TC_EVT_EFFECT_NOOP;
    // External event effect on TIOA.
    waveform_opt.aeevt    = TC_EVT_EFFECT_NOOP;
    // RC compare effect on TIOA.
    waveform_opt.acpc     = TC_EVT_EFFECT_NOOP;
    /*
     * RA compare effect on TIOA.
     * (other possibilities are none, set and clear).
     */
    waveform_opt.acpa     = TC_EVT_EFFECT_NOOP;
    /*
     * Waveform selection: Up mode with automatic trigger(reset)
     * on RC compare.
     */
    waveform_opt.wavsel   = TC_WAVEFORM_SEL_UP_MODE_RC_TRIGGER;
    // External event trigger enable.
    waveform_opt.enetrg   = false;
    // External event selection.
    waveform_opt.eevt     = 0;
    // External event edge selection.
    waveform_opt.eevtedg  = TC_SEL_NO_EDGE;
    // Counter disable when RC compare.
    waveform_opt.cpcdis   = false;
    // Counter clock stopped with RC compare.
    waveform_opt.cpcstop  = false;
    // Burst signal selection.
    waveform_opt.burst    = false;
    // Clock inversion.
    waveform_opt.clki     = false;
    // Internal source clock 3, connected to fPBA / 8.
    waveform_opt.tcclks   = TC_CLOCK_SOURCE_TC3;

    // Options for enabling TC interrupts
    tc_interrupt_t tc_interrupt;
    tc_interrupt.etrgs = 0;
    tc_interrupt.ldrbs = 0;
    tc_interrupt.ldras = 0;
    tc_interrupt.cpcs  = 1; // Enable interrupt on RC compare alone
    tc_interrupt.cpbs  = 0;
    tc_interrupt.cpas  = 0;
    tc_interrupt.lovrs = 0;
    tc_interrupt.covfs = 0;

    // Initialize the timer/counter.
    tc_init_waveform(TICK_TC, &waveform_opt);

    /*
     * Set the compare triggers.
     * We configure it to count every 1 milliseconds.
     * We want: (1 / (fPBA / 8)) * RC = 1 ms, hence RC = (fPBA / 8) / 1000
     * to get an interrupt every 10 ms.
     */
    tc_write_rc(TICK_TC, TICK_TC_CHANNEL, (sysclk_get_pba_hz() / 8 / TICK_RATE_HZ));
    // configure the timer interrupt
    tc_configure_interrupts(TICK_TC, TICK_TC_CHANNEL, &tc_interrupt);
    // Start the timer/counter.
    tc_start(TICK_TC, TICK_TC_CHANNEL);
}

void initInterrupts()
{
    // Disable all interrupts.
    cpu_irq_disable();

    // init the interrupts
    INTC_init_interrupts();

    // Enable all interrupts.
    cpu_irq_enable();
}

void initSerialConsole()
{
    // USART options.
    usart_options_t usart_options;
    usart_options.baudrate     = 57600;
    usart_options.charlength   = 8;
    usart_options.paritytype   = USART_NO_PARITY;
    usart_options.stopbits     = USART_1_STOPBIT;
    usart_options.channelmode  = USART_NORMAL_CHMODE;

    // Initialize USART in RS232 mode.
    sysclk_enable_peripheral_clock(USART);
    usart_init_rs232(USART, &usart_options, sysclk_get_peripheral_bus_hz(USART));

    // Disable all interrupts.
    cpu_irq_disable();

    INTC_register_interrupt(&usart_int_handler, USART_IRQ,
        USART_IRQ_PRIORITY);

    // Enable all interrupts.
    cpu_irq_enable();

    USART->ier = AVR32_USART_IER_RXRDY_MASK;
    gout->print("Serial console initialized.\r\n");
    usart_write_line(USART, "Serial console initialized.\r\n");
}

void initOLEDConsole()
{
    // Instantiate framebuffer class, single instance
    //~ static uint8_t framebuffer_data[128*64/8];
    //~ static SSD1306Framebuffer oled(SSD1306_SPI, SSD1306_SPI_NPCS, SSD1306_GPIO_DC_PIN, SSD1306_GPIO_RST_PIN, 128, 64, framebuffer_data);
    sysclk_enable_peripheral_clock(SSD1306_SPI);
    static SSD1306Framebuffer oled(SSD1306_SPI, SSD1306_SPI_NPCS, SSD1306_GPIO_DC_PIN, SSD1306_GPIO_RST_PIN, 128, 64);
    fb = &oled;
    fb->init();
    fb->clear();
    fb->flush();
    static FramebufferConsole oled_console(fb, Fonts::font3x5);
    gout = &oled_console;
    gout->print("OLED console initialized.\n");
    fb->flush();
}

void initConsole()
{
    initOLEDConsole();
    initSerialConsole();
}

void loop()
{
    gout->newline();
    {
        uint32_t n = system_ticks;
        char tmp[11];
        int i = sizeof(tmp) - 1;

        // Convert the given number to an ASCII decimal representation.
        tmp[i] = '\0';
        do
        {
            tmp[--i] = '0' + n % 10;
            n /= 10;
        } while (n);
        gout->print(tmp+i);
        usart_write_line(USART, tmp+i);
    }
    //~ gout->print(1, &i);
    //~ fb->text(0, 40, 1, &i, sizeof(Fonts::font3x5), Fonts::font3x5, 0);
    fb->flush();
    for(int u = 0; u < 10000000; ++u)
    {
        asm volatile ("nop\n");
    }
}

int main(int, char**)
{
    // Initialize hardware
    // set up clocks
    sysclk_init();
    // configure gpio pins and more
    board_init();
    // initialize interrupt controller
    initInterrupts();
    // initialize console hardware
    initConsole();
    // Initialize system tick timer
    initSystemTickTimer();

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
