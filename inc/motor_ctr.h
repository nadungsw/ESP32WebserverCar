#pragma once

#ifdef __cplusplus
extern "C" {
    #endif

    #include <stdlib.h>

    //#define MotorRightPin -1
    //#define MotorLeftPin -1

    uint16_t left_wheel_speed(uint16_t currentSpeed);
    uint16_t right_wheel_speed(uint16_t currentSpeed);

    #ifdef __cplusplus
}
#endif