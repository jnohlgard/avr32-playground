#include "cycle_counter.h"
#include "board.h"
#include "conf_clock.h"

/// Emulation of Arduino's millis() functionality on AVR32
/// \bug doesn't handle cycle counter wraparound very well
long millis(void)
{
    static long count = 0;
    static long milliseconds = 0;
    // Read CPU cycle counter and convert to millisecond difference
    long newcount = Get_sys_count();
    if (newcount < count) // cycle counter has wrapped since last update.
    {
        milliseconds += cpu_cy_2_ms(newcount, FCPU_HZ);
    }
    else
    {
        milliseconds += cpu_cy_2_ms(newcount - count, FCPU_HZ);
    }
    count = newcount;
    return milliseconds;
}

