#ifndef _CONFIG_HEADER_GUARD_
#define _CONFIG_HEADER_GUARD_

#include "Arduino.h"

//#define LOG_LEVEL LOG_LEVEL_VERBOSE

#define NUM_LEDS 1
#define DATA_PIN 18
#define TERMINAL_ID 1

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
        TransactionURL
    };

    void SetKey(settings_key key, char *name) {

        strcpy(connect_settings[key], name);
    }
        
    char * GetKey(settings_key key ) {
        return connect_settings[key];
    };

    void save();
    void load();
    void print();
    void clearAll();

   private:

    char connect_settings [5][SETTINGS_STR_LEN];
};

extern GlobalSettings g_settings;

#endif //guard
