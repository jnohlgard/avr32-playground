#include "system/system_init.h"
#include "board.h"
#include "conf_system.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <services/clock/sysclk.h>
#include <services/twi/twi_master.h>
#include <drivers/intc/intc.h>
#include "system/tick.h"
#include "system/console.h"

void initOLEDFramebuffer(void); // defined in hardware/$board/system_init.cpp

void initInterrupts(void)
{
    // Disable all interrupts.
    cpu_irq_disable();

    // init the interrupts
    irq_initialize_vectors();

    // Enable all interrupts.
    cpu_irq_enable();
}

void initTWI(void)
{
    static twi_master_options_t opt;
    opt.speed = CONF_SYSTEM_TWI_SPEED;
    opt.chip  = CONF_SYSTEM_TWI_ADDR;

    // Initialize the TWI master driver.
    twi_master_setup(CONF_SYSTEM_TWI, &opt);
}

void system_init(void)
{
    // Initialize hardware
    // set up clocks
    sysclk_init();
    // configure gpio pins and more
    board_init();
    // initialize interrupt controller
    initInterrupts();
    #ifdef CONF_SYSTEM_OLED
        initOLEDFramebuffer();
    #endif
    #ifdef CONF_SYSTEM_CONSOLE
        // initialize console hardware
        initConsole();
    #endif // CONF_SYSTEM_CONSOLE
    #ifdef CONF_SYSTEM_TICK_TIMER
        // Initialize system tick timer
        initSystemTickTimer();
    #endif
    #ifdef CONF_SYSTEM_TWI
        // Initialize i2c bus master
        initTWI();
    #endif
}

#ifdef __cplusplus
}
#endif
