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

#include "servo.h"
servo_t g_servos[SERVO_TIMESLOTS];
uint8_t g_current_servo = 0; // Currently active servo
uint16_t g_servo_max_value;

/**
 * \file servo.c
 * \brief Multiplexed servo outputs
 */

/**
 * \brief TC interrupt.
 *
 * The ISR handles RC compare interrupt and moves on to the next servo in the list.
 */
#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
#pragma handler = SERVO_TC_IRQ_GROUP, 1
__interrupt
#endif
static void servo_irq(void)
{
    servo_t* cur = &g_servos[g_current_servo];

    // Identify which interrupt happened and clear the interrupt flag.
    union
    {
        tc_interrupt_t s;
        int i;
    } status_convert;
    status_convert.i = tc_read_sr(SERVO_TC, SERVO_TC_CHANNEL);
    tc_interrupt_t* status = &status_convert.s;
    if (status->cpcs)
    {
        // Compare RC happened, move to next servo
        if (cur->enabled != 0)
        {
            gpio_clr_gpio_pin(cur->pin);
        }
        ++g_current_servo;
        if (g_current_servo >= SERVO_TIMESLOTS)
        {
            g_current_servo = 0;
        }
        cur = &g_servos[g_current_servo];
        //~ if (cur->value > g_servo_max_value)
        //~ {
            //~ cur->value = g_servo_max_value;
        //~ }
        // Set RA counter to next servo value
        tc_write_ra(SERVO_TC, SERVO_TC_CHANNEL, cur->value);
        // Turn on next servo in sequence to precharge while counting on this servo.
        uint8_t next_index = g_current_servo + 1;
        if (next_index >= SERVO_TIMESLOTS)
        {
            next_index = 0;
        }
        servo_t* next = &g_servos[next_index];
        if (next->enabled != 0)
        {
            gpio_set_gpio_pin(next->pin);
        }
    }
    else if (status->cpas)
    {
        // Compare RA happened, disable current gpio
        if (cur->enabled != 0)
        {
            gpio_clr_gpio_pin(cur->pin);
        }
    }
}

void initServoTimer(void)
{
    sysclk_enable_peripheral_clock(SERVO_TC);

    // Disable all interrupts.
    cpu_irq_disable();

    // Register the RTC interrupt handler to the interrupt controller.
    INTC_register_interrupt(&servo_irq, SERVO_TC_IRQ, SERVO_TC_IRQ_PRIORITY);

    // Enable all interrupts.
    cpu_irq_enable();

    // Options for waveform generation.
    tc_waveform_opt_t waveform_opt;
    // Channel selection.
    waveform_opt.channel  = SERVO_TC_CHANNEL;
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
     * (possibilities are noop, toggle, set and clear).
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
    unsigned int rc;
    // some different clocks depending on what command rate we're using.
    // This is needed because the timer counter is only 16 bits wide and will overflow otherwise.
    /*
     * SERVO_COMMAND_RATE_HZ is the command rate, i.e. pulses per second, typically 40-50Hz in analog servos
     * 2 / (SERVO_COMMAND_RATE_HZ * SERVO_TIMESLOTS) is the length of the maximum pulse, typically around 2 ms.
     * 1 / (SERVO_COMMAND_RATE_HZ * SERVO_TIMESLOTS) is the length of the minimum pulse, typically around 1 ms.
     * the max and min pulse width have a hard-coded relation of 1:2
     */
    if (SERVO_COMMAND_RATE_HZ * SERVO_TIMESLOTS > (sysclk_get_pba_hz() >> 16) / 2)
    {
        // Internal source clock 2, connected to fPBA / 2.
        waveform_opt.tcclks   = TC_CLOCK_SOURCE_TC2;
        rc = (sysclk_get_pba_hz() / 2 / SERVO_COMMAND_RATE_HZ / SERVO_TIMESLOTS);
    }
    else if (SERVO_COMMAND_RATE_HZ * SERVO_TIMESLOTS > (sysclk_get_pba_hz() >> 16) / 8)
    {
        // Internal source clock 3, connected to fPBA / 8.
        waveform_opt.tcclks   = TC_CLOCK_SOURCE_TC3;
        rc = (sysclk_get_pba_hz() / 8 / SERVO_COMMAND_RATE_HZ / SERVO_TIMESLOTS);
    }
    else if (SERVO_COMMAND_RATE_HZ * SERVO_TIMESLOTS > (sysclk_get_pba_hz() >> 16) / 32)
    {
        // Internal source clock 4, connected to fPBA / 32.
        waveform_opt.tcclks   = TC_CLOCK_SOURCE_TC4;
        rc = (sysclk_get_pba_hz() / 32 / SERVO_COMMAND_RATE_HZ / SERVO_TIMESLOTS);
    }
    else
    {
        // Internal source clock 5, connected to fPBA / 128.
        waveform_opt.tcclks   = TC_CLOCK_SOURCE_TC5;
        rc = (sysclk_get_pba_hz() / 128 / SERVO_COMMAND_RATE_HZ / SERVO_TIMESLOTS);
    }

    // Options for enabling TC interrupts
    tc_interrupt_t tc_interrupt;
    tc_interrupt.etrgs = 0;
    tc_interrupt.ldrbs = 0;
    tc_interrupt.ldras = 0;
    tc_interrupt.cpas  = 1; // Enable interrupt on RA compare
    tc_interrupt.cpbs  = 0; // RB compare
    tc_interrupt.cpcs  = 1; // Enable interrupt on RC compare
    tc_interrupt.lovrs = 0;
    tc_interrupt.covfs = 0; // Counter overflow

    // Initialize the timer/counter.
    tc_init_waveform(SERVO_TC, &waveform_opt);

    /*
     * Set the compare triggers.
     * We configure it to count every 1 milliseconds.
     * We want: (1 / (fPBA / 8)) * RC = 1 ms, hence RC = (fPBA / 8) / 1000
     * to get an interrupt every 10 ms.
     */
    tc_write_rc(SERVO_TC, SERVO_TC_CHANNEL, rc);
    g_servo_max_value = rc;
    // configure the timer interrupt
    tc_configure_interrupts(SERVO_TC, SERVO_TC_CHANNEL, &tc_interrupt);
    // Start the timer/counter.
    tc_start(SERVO_TC, SERVO_TC_CHANNEL);
}

#ifdef __cplusplus
}
#endif

#endif // CONF_SYSTEM_TICK_TIMER
