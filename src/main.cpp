//  ESP8266_ILI9341_Adafruit_demo
//
// Interfacing ESP8266 NodeMCU with ILI9341 TFT display (240x320 pixel).
//
//
// pins: TFT SPI ILI9341 --------  ESP8266 
//                 VCC  --------     VCC  - note- Wemos - 5V
//                 GND  --------     GND 
//                 CS   --------     D2
//                 RST  --------     D3
//                 D/C  --------     D4
//                 MOSI --------     D7  
//                 SCK  --------     D5       
//                 BL   --------     VCC - note - Wemos 5V
//
// open source - thanks to all contributors
 
#include <Arduino.h>
#include <Adafruit_GFX.h>                                                   // include Adafruit graphics library
#include <Adafruit_ILI9341.h>                                               // include Adafruit ILI9341 TFT library
#include <Framebuffer_GFX.h>
#include <Wire.h>
#include "ESP8266WiFi.h"
#include <SimpleSerialShell.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <freertos/queue.h>

#define TFT_CS    D2                                                        // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3                                                        // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4                                                        // TFT DC  pin is connected to NodeMCU pin D4

// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)

   Adafruit_ILI9341 tft = Adafruit_ILI9341 (TFT_CS, TFT_DC, TFT_RST);
   int delayTime = 500;

unsigned long testFillScreen () {

  unsigned long start = micros ();
   tft.fillScreen (ILI9341_BLACK);
   tft.fillScreen (ILI9341_RED);
   tft.fillScreen (ILI9341_GREEN);
   tft.fillScreen (ILI9341_BLUE);
   tft.fillScreen (ILI9341_BLACK);
   return micros () - start;
}
 
 
int showID(int /*argc*/ = 0, char** /*argv*/ = NULL)
{
    shell.println(F( "Running " __FILE__ ",\nBuilt " __DATE__));
    return 0;
};

void runshell() {
    while(1) {
      shell.executeIfInput();
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
 
void setup() {


    xTaskCreate(
            runshell,
            "Run Shell",
            1000,
            NULL,
            1,
            NULL
    );
 
   Serial.begin (115200);
   Serial.println ("ILI9341 Test!"); 

   shell.attach(Serial);
   shell.addCommand(F("id?"), showID);

   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
 
   tft.begin();
 
 
   Serial.println (F("Done!"));
}


 
 
void loop(void) {

  int n = WiFi.scanNetworks();


  for (int i = 0; i < n; i++)
  {
    tft.println(WiFi.SSID(i));
  }


  delay(100);
}
 
