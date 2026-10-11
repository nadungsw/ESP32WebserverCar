#include "motor_ctr.h"

uint16_t left_wheel_speed(uint16_t currentSpeed){
    return currentSpeed*2/5;
}

uint16_t right_wheel_speed(uint16_t currentSpeed){
    return currentSpeed*8/5;
}