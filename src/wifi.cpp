#include <WiFi.h>

#include "Arduino.h"
#include "config.h"

int WifiConnect(void) {

    String ssid = g_settings.GetKey("ssid");
    String pwd = g_settings.GetKey("WifiPWD");

    Serial.printf("Wifi connecting to %s \n\r", ssid);
	WiFi.begin(ssid.c_str(), pwd.c_str());

    int cnt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (cnt < 50)) {
		delay(500);
		Serial.print(".");
		cnt++;
    }
	Serial.println("");

    if (WiFi.status() == WL_CONNECTED) {
		return EXIT_SUCCESS;
	} else {
    	Serial.printf("\nError: Could not connect to  %s \n\r", ssid);
		return EXIT_FAILURE;
	}
}

int WifiStatus(void) {

    if (WiFi.status() == WL_CONNECTED) {
		Serial.printf("SSID: %s \n\r", WiFi.SSID().c_str());
		Serial.printf("RSSI: %d \n\r", WiFi.RSSI());
		Serial.printf("IP address: %s\n\r", WiFi.localIP().toString().c_str());
		Serial.printf("Mac Address: %s\n\r", WiFi.macAddress().c_str());
		Serial.printf("Subnet Mask: %s\n\r", WiFi.subnetMask().toString().c_str());
		Serial.printf("Gateway IP: %s\n\r", WiFi.gatewayIP().toString().c_str());
		Serial.printf("DNS: %s \n\r", WiFi.dnsIP().toString().c_str());
		return EXIT_SUCCESS;
    } else {
		Serial.printf("Wifi not connected \n\r");
		return EXIT_FAILURE;
    }
}

int WifiScan(void) {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    Serial.println("Scanning WiFi networks... ");
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
		return EXIT_FAILURE;
    } else {
        Serial.printf("%d networks found: \n\r", n);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("\t%d - %s: \t\t\t\t %d - encrypted: %s \n\r", 
            	i, WiFi.SSID(i).c_str(), WiFi.RSSI(i), 
				(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"-":"*");
            delay(10);
        }
		return EXIT_SUCCESS;
    }
}

#if 0

IPAddress local_IP(192, 168, 31, 115);
IPAddress gateway(192, 168, 31, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup()
{
  Serial.begin(115200);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
}
#endif
