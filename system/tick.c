#include "board.h"
#include "conf_system.h"
#ifdef CONF_SYSTEM_TICK_TIMER

#ifdef __cplusplus
extern "C" {
#endif

#include <drivers/gpio/gpio.h>
#include <drivers/intc/intc.h>
#include <drivers/tc/tc.h>
#include <services/clock/sysclk.h>

#include "system/tick.h"
uint32_t system_ticks = 0;

/**
 * \brief TC interrupt.
 *
 * The ISR handles RC compare interrupt and sets the update_timer flag to
 * update the timer value.
 */
#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
#pragma handler = TICK_TC_IRQ_GROUP, 1
__interrupt
#endif
static void tick_irq(void)
{
    // Increment the ms seconds counter
    ++system_ticks;

    // Clear the interrupt flag. This is a side effect of reading the TC SR.
    tc_read_sr(TICK_TC, TICK_TC_CHANNEL);

    // specify that an interrupt has been raised
    //~ update_timer = true;
    // Toggle a GPIO pin (this pin is used as a regular GPIO pin).
    gpio_tgl_gpio_pin(TICK_TOGGLE_PIN);
}

void initSystemTickTimer(void)
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

#ifdef __cplusplus
}
#endif

#endif // CONF_SYSTEM_TICK_TIMER
