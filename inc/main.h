#ifndef __MAIN_H
#define __MAIN_H

#include <Arduino.h>

#include "CarWeb.h"
#include "motor_ctr.h"

#define ESP_DEBUG 1
#if ESP_DEBUG
    #include <stdio.h>
    #define mPrint(...) printf(__VA_ARGS__)
#else
    #define mPrint(...) ((void)0)
#endif

void setup();
void loop();

#endif