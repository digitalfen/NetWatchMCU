#include "WiFiService.h"

void WiFiService::startAccessPoint() {
  GlobalValues::ap_mode = true;
  WiFi.softAP(GlobalValues::ap_ssid, GlobalValues::ap_pwrd);
  if (WiFi.softAPIP() != IPAddress(0, 0, 0, 0)) {
    delay(1000);
    Serial.println("Iniciando Access Point...");
  }
  Serial.println("Access Point está ativo\nIP: " + WiFi.softAPIP().toString());
}

void WiFiService::stopAccessPoint() {
  GlobalValues::ap_mode = false;
  WiFi.softAPdisconnect(true);
  Serial.println("AP encerrado");
}

void WiFiService::startStation() {
  GlobalValues::st_mode = true;
  WiFi.begin(GlobalValues::st_ssid, GlobalValues::st_pwrd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi\nIP: " + WiFi.localIP().toString());
}

void WiFiService::stopStation() {
  GlobalValues::st_mode = false;
  WiFi.disconnect();
  Serial.println("Desconectado da rede");
}

void WiFiService::WiFiStateListener(ESP8266WiFiClass* wifi) {
  bool ap = GlobalValues::ap_mode;
  bool st = GlobalValues::st_mode;

  if (GlobalValues::ap_mode && GlobalValues::st_mode) {
  }

  if (!GlobalValues::st_mode) {
    IPAddress zeroIP(0, 0, 0, 0);
    if (GlobalValues::ap_mode && WiFi.softAPIP() == zeroIP) {
      WiFiService::startAccessPoint();
    } else if (!GlobalValues::ap_mode && WiFi.softAPIP() != zeroIP) {
      WiFiService::stopAccessPoint();
    }
  }

  if (!GlobalValues::ap_mode) {
    if (GlobalValues::st_mode && WiFi.status() == WL_DISCONNECTED) {
      WiFiService::startStation();
    } else if (!GlobalValues::st_mode && WiFi.status() == WL_CONNECTED) {
      WiFiService::stopStation();
    }
  }
}
