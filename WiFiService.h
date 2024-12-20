#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include "GlobalValues.h"
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <Arduino.h>

class WiFiService {
public:
  static void WiFiStateListener(ESP8266WiFiClass* wifi);
  static void startAccessPoint();
  static void stopAccessPoint();
  static void startStation();
  static void stopStation();
};

#endif
