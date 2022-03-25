#include "config.h"

#include <EEPROM.h>
#include <Preferences.h>
#include <nvs_flash.h>

#include "Arduino.h"

Preferences prefs;

void GlobalSettings::clearAll() {
    prefs.begin("connect", false);
    prefs.clear();
    prefs.end();
}

void GlobalSettings::save() {
    prefs.begin("connect", false);

    char str[100] = {0};
    for (auto it = lookup.begin(); it != lookup.end(); it++) {
        String key = it->first;
        String value = it->second;

        // TODO: using String directly does not work
        prefs.putString(key.c_str(), value.c_str());
    }

    prefs.end();
}

void GlobalSettings::load() {
    prefs.begin("connect", false);

    char str[100] = {0};
    for (auto it = lookup.begin(); it != lookup.end(); it++) {
        String key = it->first;

        // TODO: using String directly does not work
        prefs.getString(key.c_str(), str,
                        SETTINGS_STR_LEN);  // it->second.c_str());
        String value(str);
        lookup[key] = value;
    }

    prefs.end();
}

void GlobalSettings::print() {
    // Serial.printf("ssid: %s\n\r", connect_settings[SSID]);
    // Serial.printf("WifiPWD: %s\n\r", connect_settings[PWD]);
    // Serial.printf("ServerName: %s\n\r", connect_settings[ServerName]);
    // Serial.printf("TerminalURL: %s\n\r", connect_settings[TerminalURL]);
    // Serial.printf("TransactionURL: %s\n\r",
    // connect_settings[TransactionURL]);

    for (auto it = lookup.begin(); it != lookup.end(); it++) {
        Serial.printf("%s: %s \n\r", it->first.c_str(), it->second.c_str());
    }
}
