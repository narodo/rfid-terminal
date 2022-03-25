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


// Define the array of leds
//CRGB leds[NUM_LEDS];

//
//Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);


//String Name = "TROCKNEN";
//String Location = "Waschkueche";
//String Price = "2.80";

//
//settings::SetTerminalUrl("terminals");
//settings::SetTransactionUrl("transactions");

//websettings.serverName = String("http://192.168.0.100:8080/");
//websettings.TerminalURL = String(settings.serverName + "/terminal/");
//websettings.TransactionURL = String(settings.serverName + "/transactions/");

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

    //String httpGETRequest();


    //Serial.printf("Serial Number: %u \n", ESP.getEfuseMac());
    //Serial.printf("server string : %s \n", g_settings.GetServerName());
    //Serial.printf("WifiSSID string : %s \n", g_settings.GetWifiSSID());

    //DisplayInit();
    //testTextbox();
    // helloWorldUTF8();

    // helloArduino();
    // DisplayPrintStatus(Name, Location, Price);
    // helloFullScreenPartialMode();

    //delay(2000);
    // DisplayError("No WiFi", "notext");
    /*
       WiFi.begin(ssid, passwd);
       Serial.println("Connecting");
       while(WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
       }

       Serial.println("");
       Serial.print("Connected to WiFi network with IP Address: ");
       Serial.println(WiFi.localIP());

       Serial.println(httpGETRequest("http://192.168.0.100:8080/terminal/1"));

       Serial.println ("-- Begin -- ");
       nfc.begin();



       uint32_t versiondata = nfc.getFirmwareVersion();
       if (! versiondata) {
       Serial.print("Didn't find PN53x board");
       while (1); // halt
       }

    // Got ok data, print it out!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF,
    HEX); Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF,
    DEC); Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

    // Set the max number of retry attempts to read from a card
    // This prevents us from waiting forever for a card, which is
    // the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0xFF);

    // configure board to read RFID tags
    nfc.SAMConfig();

    Serial.println("Waiting for an ISO14443A card");
    */
}

void loop(void) {

    shell.executeIfInput();
    /*
       boolean success;
       uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };	// Buffer to store the returned
    UID uint8_t uidLength;				// Length of the UID (4
    or 7 bytes depending on ISO14443A card type)

    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
    // 'uid' will be populated with the UID, and uidLength will indicate
    // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0],
    &uidLength);

    if (success) {
    leds[0] = CRGB::Green;
    leds[0].fadeLightBy(64);
    FastLED.show();

    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println("
    bytes"); Serial.print("UID Value: "); for (uint8_t i=0; i < uidLength; i++)
    {
    Serial.print(" 0x");Serial.print(uid[i], HEX);
    }
    Serial.println("");
    // Wait 1 second before continuing
    delay(1000);
    }
    else
    {
    // PN532 probably timed out waiting for a card
    Serial.println("Timed out waiting for a card");
    }
    */
}
