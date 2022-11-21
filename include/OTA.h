#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <String.h>

void enableWiFi(char *ssid, char *password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

	if	(WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		ESP.restart();
	}
}

void enableOTA(const char *hostName) {
	//Enabled "Over The Air" updates so that the ESPs can be updated remotely 
	ArduinoOTA.setPort(8266);
	ArduinoOTA.setHostname(hostName);
    MDNS.setHostname(hostName);

	ArduinoOTA.onStart([]() {
		// MDNS.close(); //Close to not interrupt other devices
		Serial.println("OTA Update Started...");
	});
	ArduinoOTA.onEnd([]() {
		Serial.println("\nOTA Update Ended!");
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r\n", (progress / (total / 100)));
	});

	ArduinoOTA.begin();
}