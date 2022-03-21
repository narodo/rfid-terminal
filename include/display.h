#ifndef _DISPLAY_HEADER_GUARD_
#define _DISPLAY_HEADER_GUARD_

#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_GFX.h>

#include "GxEPD2/GxEPD2_display.h"

void DisplayInit();

void helloWorld();
void DisplayPrintStatus(String Name, String Location, String Price);
void DisplayError(String Error, String Text);
void helloWorldUTF8();

void helloFullScreenPartialMode();
void helloArduino();
void testTextbox();

#endif
