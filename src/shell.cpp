
#include <Arduino.h>
#include <SimpleSerialShell.h>
#include "shell.h"

#include <map>

#include "config.h"

extern GlobalSettings g_settings;

int loadConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.load();
    return EXIT_SUCCESS;
}

int saveConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.save();
    return EXIT_SUCCESS;
}

int printConfig(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    g_settings.print();
    return EXIT_SUCCESS;
}

int updateConfig(int argc, char** argv) {
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

int showID(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    shell.println(F("Running " __FILE__ ", Built " __DATE__));
    return EXIT_SUCCESS;
};

int restartMCU(int /*argc*/ = 0, char** /*argv*/ = NULL) {
    shell.println(F("Restarting MCU!"));
    ESP.restart();
    return EXIT_SUCCESS;
};

int addShellCommands(SimpleSerialShell& shell) {
    ADD_COMMAND("restart", "\t - [restarts MCU]", restartMCU);
    ADD_COMMAND("showID", "\t - [prints build date]", showID);
    ADD_COMMAND("printConfig", "\t - [prints config keys]", printConfig);
    ADD_COMMAND("loadConfig", "\t - [loads config from flash]", loadConfig);
    ADD_COMMAND("saveConfig", "\t - [saves config to flash]", saveConfig);
    ADD_COMMAND(
	"updateConfig",
	"\t - [updates config parameter, requires saveConfig to make permanent ] \n\r \
			-> updateConfig <config key >  <value> \n\r \
			-> e.g.: updateConfig WifiPWD newpassword \n\r",
	updateConfig);

    return EXIT_SUCCESS;
}
