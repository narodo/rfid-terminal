#include "config.h"

#include <EEPROM.h>
#include <nvs_flash.h>
#include <Preferences.h>
#include "Arduino.h"

Preferences prefs;


void GlobalSettings::clearAll() {
    prefs.begin("connect", false);
    prefs.clear();
    prefs.end();
}

void GlobalSettings::save() {

    prefs.begin("connect", false);

    prefs.putString("ssid",            per_settings.WifiSSID);
    prefs.putString("WifiPWD",         per_settings.WifiPWD);
    prefs.putString("ServerName",      per_settings.ServerName);
    prefs.putString("TerminalURL",     per_settings.TerminalURL);
    prefs.putString("TransactionURL",  per_settings.TransactionURL);

    prefs.end();
}

void GlobalSettings::load() {


    prefs.begin("connect", false, "nvs");

    prefs.getString("ssid",         per_settings.WifiSSID       ,SETTINGS_STR_LEN);
    prefs.getString("WifiPWD",      per_settings.WifiPWD        ,SETTINGS_STR_LEN);
    prefs.getString("ServerName",   per_settings.ServerName     ,SETTINGS_STR_LEN);
    prefs.getString("TerminalURL",  per_settings.TerminalURL    ,SETTINGS_STR_LEN);
    prefs.getString("TransactionURL",per_settings.TransactionURL,SETTINGS_STR_LEN);

    prefs.end();
}



void GlobalSettings::print() {

    Serial.printf("---- Global Settings ---- \n");
    Serial.printf("ssid: %s\n",          per_settings.WifiSSID      );
    Serial.printf("WifiPWD: %s\n",       per_settings.WifiPWD       );
    Serial.printf("ServerName: %s\n",    per_settings.ServerName    );
    Serial.printf("TerminalURL: %s\n",   per_settings.TerminalURL   );
    Serial.printf("TransactionURL: %s\n",per_settings.TransactionURL);

}
