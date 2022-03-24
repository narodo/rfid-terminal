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

    prefs.putString("ssid", connect_settings[SSID]);
    prefs.putString("WifiPWD", connect_settings[PWD]);
    prefs.putString("ServerName", connect_settings[ServerName]);
    prefs.putString("TerminalURL", connect_settings[TerminalURL]);
    prefs.putString("TransactionURL", connect_settings[TransactionURL]);
    prefs.end();
}

void GlobalSettings::load() {
    prefs.begin("connect", false, "nvs");

    prefs.getString("ssid", connect_settings[SSID], SETTINGS_STR_LEN);
    prefs.getString("WifiPWD", connect_settings[PWD], SETTINGS_STR_LEN);
    prefs.getString("ServerName", connect_settings[ServerName],
                    SETTINGS_STR_LEN);
    prefs.getString("TerminalURL", connect_settings[TerminalURL],
                    SETTINGS_STR_LEN);
    prefs.getString("TransactionURL", connect_settings[TransactionURL],
                    SETTINGS_STR_LEN);

    prefs.end();
}

void GlobalSettings::print() {
    Serial.printf("ssid: %s\n\r", connect_settings[SSID]);
    Serial.printf("WifiPWD: %s\n\r", connect_settings[PWD]);
    Serial.printf("ServerName: %s\n\r", connect_settings[ServerName]);
    Serial.printf("TerminalURL: %s\n\r", connect_settings[TerminalURL]);
    Serial.printf("TransactionURL: %s\n\r", connect_settings[TransactionURL]);
}
