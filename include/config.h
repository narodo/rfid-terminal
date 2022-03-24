#ifndef _CONFIG_HEADER_GUARD_
#define _CONFIG_HEADER_GUARD_

//#include <ArduinoLog.h>
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
    void SetServerName(char * name) {
        strcpy(per_settings.ServerName , name);
    }
    void SetTerminalURL(char * name) {
        strcpy(per_settings.TerminalURL , name);
    }
    void SetTransactionURL(char * name) {
        strcpy(per_settings.TransactionURL , name);
    }

    void SetWifiSSID(char * name) {
        strcpy(per_settings.WifiSSID , name);
    }

    void SetWifiPWD(char * name) {
        strcpy(per_settings.WifiPWD , name);
    }

    char * GetServerName() {
        return per_settings.ServerName;
    };
    char * GetTerminalURL() {
        return per_settings.TerminalURL;
    };
    char * GetTransactionURL() {
        return per_settings.TransactionURL;
    };

    char * GetWifiSSID() {
        return per_settings.WifiSSID;
    };

    char * GetWifiPWD() {
        return per_settings.WifiPWD;
    };


    void save();
    void load();
    void print();
    void clearAll();

   private:

    struct persistent_settings {
        char WifiSSID[SETTINGS_STR_LEN];
        char WifiPWD[SETTINGS_STR_LEN];
        char ServerName[SETTINGS_STR_LEN];
        char TerminalURL[SETTINGS_STR_LEN];
        char TransactionURL[SETTINGS_STR_LEN];
    };

    struct persistent_settings per_settings;

    //};
};

extern GlobalSettings g_settings;

#endif //guard
