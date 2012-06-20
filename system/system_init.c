#include "system/system_init.h"
#include "board.h"
#include "conf_system.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <services/clock/sysclk.h>
#include <drivers/intc/intc.h>
#include "system/tick.h"
#include "system/console.h"

void initOLEDFramebuffer(void); // defined in hardware/$board/system_init.cpp

void initInterrupts(void)
{
    // Disable all interrupts.
    cpu_irq_disable();

    // init the interrupts
    INTC_init_interrupts();

    // Enable all interrupts.
    cpu_irq_enable();
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
}

#ifdef __cplusplus
}
#endif
