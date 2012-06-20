#ifndef SYSTEM_SYSTEM_H
#define SYSTEM_SYSTEM_H
#include "conf_system.h"

#include "system_init.h"

#ifdef CONF_SYSTEM_TICK_TIMER
#include "tick.h"
#endif

#ifdef CONF_SYSTEM_CONSOLE
#include "console.h"
#endif

#ifdef __cplusplus
#include "framebuffer.hpp"
#include "streams.hpp"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif // SYSTEM_SYSTEM_INIT_H
