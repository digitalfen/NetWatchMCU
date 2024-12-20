#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "WebService.h"
#include "WiFiService.h"


ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  WebService::registerDefaultRoutes(&server);

  server.begin();

  WiFi.softAP("5G_FELICIO", "mouse123");
}

void loop() {
  WiFiService::WiFiStateListener(&WiFi);
  server.handleClient();
}
