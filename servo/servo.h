#ifndef SERVO_SERVO_H
#define SERVO_SERVO_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

void initServoTimer(void);

// 20 ms period
// 1-2 ms pulse width means we can cram in 20 servos using only one counter.
#define SERVO_TIMESLOTS 20

typedef struct
{
    //~ public:
    uint32_t pin;
    uint16_t value;
    uint8_t enabled;
    //~ ServoController() : pin(0), value(32767), enabled(0) {}
} servo_t;

extern servo_t g_servos[SERVO_TIMESLOTS];
//~ extern uint8_t g_current_servo; // Currently active servo
extern uint16_t g_servo_max_value;

#ifdef __cplusplus
}
#endif
#endif // SERVO_SERVO_H
