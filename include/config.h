#ifndef _CONFIG_HEADER_GUARD_
#define _CONFIG_HEADER_GUARD_

#include <map>
#include "Arduino.h"

//#define LOG_LEVEL LOG_LEVEL_VERBOSE

#define NUM_LEDS 1
#define DATA_PIN 18
#define TERMINAL_ID 1

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define SETTINGS_STR_LEN 50

//#define PN532_IRQ (12)
//#define PN532_RESET (13)


class GlobalSettings {
   public:

    enum settings_key {
        SSID,
        PWD,
        ServerName,
        TerminalURL,
        TransactionURL,
        INVALID
    };

    int SetKey(String key, String value) {

        auto search = lookup.find(key);
        if (search != lookup.end()) {
            search->second = value;
            return EXIT_SUCCESS;
        } else {
            Serial.printf("Key %s not found! \n\r", key);
            return EXIT_FAILURE;
        }
    }
        
    String GetKey(String key ) {
        auto search = lookup.find(key);
        if (search != lookup.end()) {
            return search->second;
        } else {
            Serial.printf("Key %s not found! \n\r", key);
            return "";
        }
        
    };

    void printKeys(void) {
        for (auto it = lookup.begin(); it != lookup.end(); it++)
        {
          Serial.printf("\t\t --> %s \n\r", it->first.c_str());
        }
    }

    void save();
    void load();
    void print();
    void clearAll();

   private:

    std::map<String, String> lookup {
        {"ssid",        "-empty-"},
        {"WifiPWD",     "-empty-"},
        {"ServerName",  "-empty-"},
        {"TerminalURL", "-empty-"},
        {"TransactionURL", "-empty-"},
    };
    //char connect_settings [5][SETTINGS_STR_LEN];
};

extern GlobalSettings g_settings;

#endif //guard
