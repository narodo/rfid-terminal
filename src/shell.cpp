#include <Arduino.h>
#include <map>
#include <WiFi.h>
#include <SimpleSerialShell.h>
#include "shell.h"

#include "config.h"

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

int cmd_connectWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {

    String ssid = g_settings.GetKey("ssid");
    String pwd = g_settings.GetKey("WifiPWD");

    shell.printf("Wifi connecting to %s \n\r", ssid);
	WiFi.begin(ssid.c_str(), pwd.c_str());

    int cnt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (cnt < 50)) {
		delay(500);
		shell.print(".");
		cnt++;
    }
	shell.println("");

    if (WiFi.status() == WL_CONNECTED) {
		return EXIT_SUCCESS;
	} else {
    	shell.printf("\nError: Could not connect to  %s \n\r", ssid);
		return EXIT_FAILURE;
	}
}

int cmd_printWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {

    if (WiFi.status() == WL_CONNECTED) {
		shell.printf("SSID: %s \n\r", WiFi.SSID().c_str());
		shell.printf("RSSI: %d \n\r", WiFi.RSSI());
		shell.printf("IP address: %s\n\r", WiFi.localIP().toString().c_str());
		shell.printf("Mac Address: %s\n\r", WiFi.macAddress().c_str());
		shell.printf("Subnet Mask: %s\n\r", WiFi.subnetMask().toString().c_str());
		shell.printf("Gateway IP: %s\n\r", WiFi.gatewayIP().toString().c_str());
		shell.printf("DNS: %s \n\r", WiFi.dnsIP().toString().c_str());
		return EXIT_SUCCESS;
    } else {
		shell.printf("Wifi not connected \n\r");
		return EXIT_FAILURE;
    }
}

int cmd_scanWifi(int /*argc*/ = 0, char** /*argv*/ = NULL) {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    shell.println("Scanning WiFi networks... ");
    int n = WiFi.scanNetworks();
    shell.println("scan done");
    if (n == 0) {
        shell.println("no networks found");
		return EXIT_FAILURE;
    } else {
        shell.printf("%d networks found: \n\r", n);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            shell.printf("\t%d - %s: \t\t\t\t %d - encrypted: %s \n\r", 
            	i, WiFi.SSID(i).c_str(), WiFi.RSSI(i), 
				(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"-":"*");
            delay(10);
        }
		return EXIT_SUCCESS;
    }
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
	-> e.g.: updateConfig WifiPWD newpassword", cmd_updateConfig);
    ADD_COMMAND("Wificonnect", "\t - [connect to Wifi]", cmd_connectWifi);
    ADD_COMMAND("Wifistatus", "\t - [print wifi status ]", cmd_printWifi);
    ADD_COMMAND("Wifiscan", "\t - [scan wifi ]", cmd_scanWifi);

    return EXIT_SUCCESS;
}
