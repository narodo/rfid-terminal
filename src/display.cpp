#include <Framebuffer_GFX.h>
#include <Adafruit_GFX.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <ArduinoLog.h>
#include "config.h"
#include "display.h"
#include "layouts.h"

GxEPD2_DISPLAY display(GxEPD2_DRIVER_CLASS(/*CS=5*/ EPD_CS, /*DC=*/ 21, /*RST=*/ 20, /*BUSY=*/ 19));

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void DisplayInit () {
  //display.init(115200, true, 2, false);
  display.init();
  display.setRotation(1);
  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
}

void testTextbox() {


    Serial.print("test Textbox");

    Layout::LayoutMain MainPage;
    MainPage.TB_title.updateContent("Waschküche");
    MainPage.TB_main.updateContent("TROCKNER");
    MainPage.TB_sub.updateContent(" 2.50E");

    //
    MainPage.refreshAll();
    //
    delay(5000);
    MainPage.updateTitle("New Title");
    display.hibernate();

    delay(5000);
    MainPage.updateMain("New Main");
    display.hibernate();

    delay(5000);
    MainPage.refreshAll();
    display.hibernate();
    //display.firstPage();
    //Serial.printf("\n-- starting render -- \n");
    //do
    //{
      //display.fillScreen(GxEPD_WHITE);
      //TB1.render();
      //TB2.render();
      //TB3.render();
    //}
    //while (display.nextPage());
    //display.hibernate();
}

