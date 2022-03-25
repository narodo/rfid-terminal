
#include <Arduino.h>
#include <map>
#include <SimpleSerialShell.h>
#include "shell.h"

#include "config.h"
#include "wifi.h"

int cmd_loadConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.load();
    return EXIT_SUCCESS;
}

int cmd_saveConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.save();
    return EXIT_SUCCESS;
}

int cmd_printConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.print();
    return EXIT_SUCCESS;
}

int cmd_updateConfig(int argc, char** argv) {
    if (argc != 3) {
	shell.println(
	    F("Error: updateConfig requires two parameter \n\r \
			-> e.g.: updateConfig WifiPWD newpassword \n\r"));

	return EXIT_FAILURE;
    }

    String key(argv[1]);
    String value(argv[2]);

    if (g_settings.SetKey(key, value) != EXIT_SUCCESS) {
		shell.printf("Error: key %s not found!\n\r", argv[1]);
		shell.printf("\t valid keys are: \n\r");
		return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int cmd_showID(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    shell.println(F("Running " __FILE__ ", Built " __DATE__));
    return EXIT_SUCCESS;
};

int cmd_restartMCU(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    shell.println(F("Restarting MCU!"));
    ESP.restart();
    return EXIT_SUCCESS;
};

int cmd_printWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {
	return WifiStatus();
}

int cmd_connectWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {
	return WifiConnect();
}

int cmd_scanWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {
	return WifiScan();
}

int addShellCommands(SimpleSerialShell& shell) {
    ADD_COMMAND("restart", "\t - [restarts MCU]", cmd_restartMCU);
    ADD_COMMAND("showID", "\t - [prints build date]", cmd_showID);
    ADD_COMMAND("Configprint", "\t - [prints config keys]", cmd_printConfig);
    ADD_COMMAND("Configload", "\t - [loads config from flash]", cmd_loadConfig);
    ADD_COMMAND("Configsave", "\t - [saves config to flash]", cmd_saveConfig);
    ADD_COMMAND( "Configupdate",
	"\t - [updates config parameter, requires saveConfig to make permanent ] \n\r \
			-> updateConfig <config key >  <value> \n\r \
			-> e.g.: updateConfig WifiPWD newpassword \n\r", cmd_updateConfig);
    ADD_COMMAND("Wificonnect", "\t - [connect to Wifi]", cmd_connectWifi);
    ADD_COMMAND("Wifistatus", "\t - [print wifi status ]", cmd_printWifi);
    ADD_COMMAND("Wifiscan", "\t - [scan wifi ]", cmd_scanWifi);

    return EXIT_SUCCESS;
}
