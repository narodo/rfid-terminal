#include <Arduino.h>
#include <Adafruit_PN532.h>
#include <ArduinoLog.h>
#include <FastLED.h>
#include <Wire.h>
#include <SimpleSerialShell.h>

#include "display.h"
#include "web.h"
#include "config.h"
#include "shell.h"



const char* ssid   = "ssid";
const char* passwd = "pwd";
GlobalSettings g_settings;


void setup() {

    Serial.begin(115200);
    while (!Serial && !Serial.available()) {
    }

    shell.attach(Serial);
    addShellCommands(shell);

    g_settings.load();
    shell.println(F("\n\n-- Loaded config from flash  --"));
    g_settings.print();
    shell.println(F("-- -- -- -- -- -- -- -- -- -- --"));
}

void loop(void) {
    shell.executeIfInput();
}
