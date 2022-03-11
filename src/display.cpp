#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include "GxEPD2/GxEPD2_display_selection.h"
#include "GxEPD2/GxEPD2_selection_check.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Framebuffer_GFX.h>
#include "display.h"

const char HelloWorld[] = "Hello World! - ";

void DisplayInit () {
  display.init(115200, true, 2, false);
}

void helloWorld()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());

  display.hibernate();
}