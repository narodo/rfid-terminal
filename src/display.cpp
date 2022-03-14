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
    //Serial.print(u8g2Fonts.getFontAscent()); 
    //Serial.print(", "); Serial.print(u8g2Fonts.getFontDescent()); Serial.println(")");

    Layout::TextBox TB1(0, 0, 280, 40, u8g2_font_helvB24_te, GxEPD_WHITE, GxEPD_BLACK , Layout::right);
    Layout::TextBox TB2(10, 42, 260, 40, u8g2_font_helvB12_te, GxEPD_WHITE, GxEPD_BLACK, Layout::left );
    Layout::TextBox TB3(0, 84 , 280, 40, u8g2_font_helvB24_te, GxEPD_WHITE, GxEPD_BLACK );

    TB1.setAlignment(Layout::right);
    TB1.setStyle(Layout::box);
    TB1.updateContent("My TB1 test!");
    TB2.setAlignment(Layout::left);
    TB2.setStyle(Layout::box);
    TB2.updateContent("My TB2 test!");
    TB3.setAlignment(Layout::center);
    TB3.setStyle(Layout::box);
    TB3.updateContent("My TB3 super long test!");

    display.setFullWindow();
    display.firstPage();
    Serial.printf("\n-- starting render -- \n");
    do
    {
      display.fillScreen(GxEPD_WHITE);
      TB1.render();
      TB2.render();
      TB3.render();
    }
    while (display.nextPage());
    display.hibernate();
}

//void helloWorld()
//{
  //display.setRotation(1);
  //display.setFont(&FreeMonoBold9pt7b);
  //display.setTextColor(GxEPD_BLACK);
  //int16_t tbx, tby; uint16_t tbw, tbh;
  //display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
   //center the bounding box by transposition of the origin:
  //uint16_t x = ((display.width() - tbw) / 2) - tbx;
  //uint16_t y = ((display.height() - tbh) / 2) - tby;
  //display.setFullWindow();
  //display.firstPage();
  //do
  //{
    //display.fillScreen(GxEPD_WHITE);
    //display.setCursor(x, y);
    //display.print(HelloWorld);
  //}
  //while (display.nextPage());

  //display.hibernate();
//}



/*
// 296x128
void DisplayPrintStatus(String Title, String Main, String Sub) {
  int16_t loc_tbx, loc_tby; uint16_t loc_tbw, loc_tbh;
  int16_t prc_tbx, prc_tby; uint16_t prc_tbw, prc_tbh;
  int16_t name_tbx, name_tby; uint16_t name_tbw, name_tbh;


  display.setRotation(1);

  u8g2Fonts.setFont(u8g2_font_helvB24_te);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall

  int16_t tw = u8g2Fonts.getUTF8Width(HelloWorld); // text box width
  int16_t ta = u8g2Fonts.getFontAscent(); // positive
  int16_t td = u8g2Fonts.getFontDescent(); // negative; in mathematicians view
  int16_t th = ta - td; // text box height
  //Serial.print("ascent, descent ("); Serial.print(u8g2Fonts.getFontAscent()); Serial.print(", "); Serial.print(u8g2Fonts.getFontDescent()); Serial.println(")");
  // center bounding box by transposition of origin:
  // y is base line for u8g2Fonts, like for Adafruit_GFX True Type fonts
  uint16_t x = (display.width() - tw) / 2;
  uint16_t y = (display.height() - th) / 2 + ta;

  display.getTextBounds(Location, 0, 0, &loc_tbx, &loc_tby, &loc_tbw, &loc_tbh);
  display.getTextBounds(Price, 0, 0, &prc_tbx, &prc_tby, &prc_tbw, &prc_tbh);
  display.setTextColor(GxEPD_BLACK);

  display.setFont(&FreeMonoBold24pt7b);
  display.getTextBounds(Name, 0, 0, &name_tbx, &name_tby, &name_tbw, &name_tbh);
  
   //center the bounding box by transposition of the origin:
  uint16_t loc_x = ((display.width() - loc_tbw) / 2) - loc_tbx; // center 
  uint16_t loc_y = loc_tbh + 10;
  uint16_t name_x = ((display.width() - name_tbw) / 2) - name_tbx; // center 
  uint16_t name_y = name_tbh +  loc_y + 10;
  uint16_t prc_x = ((display.width() - prc_tbw) / 2) - prc_tbx; //center
  uint16_t prc_y =  prc_tbh +  name_y + 20;

  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(loc_x, loc_y);
    display.print(Location);

    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(name_x, name_y);
    display.print(Name);

    display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(prc_x, prc_y);
    display.print(Price);
  }
  while (display.nextPage());

  display.hibernate();
}

const char HelloWorld[] = "Hello Wörld!";
const char HelloArduino[] = "Hello Arduino!";
const char HelloEpaper[] = "Hello E-Paper!";

void helloWorldUTF8()
{
  //Serial.println("helloWorld");
  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  display.setPartialWindow(0, 0, display.width(), display.height());

  display.setRotation(1);
  u8g2Fonts.setFontMode(1);                 // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);            // left to right (this is default)
  u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg);         // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_helvR14_tf);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  int16_t tw = u8g2Fonts.getUTF8Width(HelloWorld); // text box width
  int16_t ta = u8g2Fonts.getFontAscent(); // positive
  int16_t td = u8g2Fonts.getFontDescent(); // negative; in mathematicians view
  int16_t th = ta - td; // text box height
  //Serial.print("ascent, descent ("); Serial.print(u8g2Fonts.getFontAscent()); Serial.print(", "); Serial.print(u8g2Fonts.getFontDescent()); Serial.println(")");
  // center bounding box by transposition of origin:
  // y is base line for u8g2Fonts, like for Adafruit_GFX True Type fonts
  uint16_t x = (display.width() - tw) / 2;
  uint16_t y = (display.height() - th) / 2 + ta;
  //Serial.print("bounding box    ("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.print(", "); Serial.print(tw); Serial.print(", "); Serial.print(th); Serial.println(")");
  display.firstPage();
  do
  {
    display.fillScreen(bg);
    u8g2Fonts.setCursor(x, y); // start writing at this position
    u8g2Fonts.print(HelloWorld);
  }
  while (display.nextPage());
  //display.hibernate();
  //Serial.println("helloWorld done");
}


void DisplayError(String Error, String Text) {

  int16_t tbx, tby; uint16_t tbw, tbh;
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setFont(&FreeMonoBold18pt7b);
  display.getTextBounds(Error, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;

  //display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);

    display.setFont(&FreeMonoBold18pt7b);
    display.setCursor(x, y);
    display.print(Error);
  }
  while (display.nextPage());

  //display.hibernate();

}

void helloFullScreenPartialMode()
{
  //Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  const char* updatemode;
  if (display.epd2.hasFastPartialUpdate)
  {
    updatemode = fpm;
  }
  else if (display.epd2.hasPartialUpdate)
  {
    updatemode = spm;
  }
  else
  {
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hwx, hwy);
    display.print(HelloWorld);
    display.setCursor(utx, uty);
    display.print(fullscreen);
    display.setCursor(umx, umy);
    display.print(updatemode);
  }
  while (display.nextPage());
  //Serial.println("helloFullScreenPartialMode done");
}

void helloArduino()
{
  //Serial.println("helloArduino");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // align with centered HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // height might be different
  display.getTextBounds(HelloArduino, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t y = ((display.height() / 4) - tbh / 2) - tby; // y is base line!
  // make the window big enough to cover (overwrite) descenders of previous text
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = (display.height() / 4) - wh / 2;
  //display.setPartialWindow(0, wy, display.width(), wh);
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    //display.drawRect(x, y - tbh, tbw, tbh, GxEPD_BLACK);
    display.setCursor(x, y);
    display.print(HelloArduino);
  }
  while (display.nextPage());
  delay(1000);
  //Serial.println("helloArduino done");
}
*/
