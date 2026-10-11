#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
//#include <SPIFFS.h> //He thong tep tin

#include "motor_ctr.h"

void handRoot();
void handleControl();
void WebInit();
void WebCtrl();