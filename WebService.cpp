#include "WebService.h"

#include "GlobalValues.h"
#include <ESP8266WiFi.h>


void WebService::registerDefaultRoutes(ESP8266WebServer* server) {

  server->on("/admin", HTTP_GET, [server]() {
    server->send(200, "text/html", WebPages::admin());
  });

  server->on("/results", HTTP_GET, [server]() {
    server->send(200, "text/html", WebPages::results());
  });

  server->on("/error", HTTP_GET, [server]() {
    server->send(400, "text/html", "Ops... Something is happening!");
  });

  server->on("/function", HTTP_GET, [server]() {
    String path = "/";
    String callable = "";
    if (server->hasArg("path")) {
      path = server->arg("path");
    };
    if (server->hasArg("callable")) {
      callable = server->arg("callable");
      if (callable == "start_scan") {
        if (!GlobalValues::scanning) {
          GlobalValues::scanning = true;
        }
      }
      if (callable == "stop_scan") {
        if (GlobalValues::scanning) {
          GlobalValues::scanning = false;
        }
      }
      if (callable == "save_global") {
        if (server->hasArg("scan_repeat")) {
          GlobalValues::scan_repeat = server->arg("scan_repeat").toInt();
        };
        if (server->hasArg("scan_interval")) {
          GlobalValues::scan_interval = server->arg("scan_duration").toInt();
        };
        if (server->hasArg("scan_results")) {
          GlobalValues::scan_results = server->arg("scan_results");
        };
        if (server->hasArg("ap_ssid")) {
          GlobalValues::ap_ssid = server->arg("ap_ssid");
        };
        if (server->hasArg("ap_pwrd")) {
          GlobalValues::ap_pwrd = server->arg("ap_pwrd");
        };
        if (server->hasArg("scanning")) {
          GlobalValues::scanning = (server->arg("scanning") == "true") ? true : false;
        };
        if (server->hasArg("ap_mode")) {
          GlobalValues::ap_mode = (server->arg("ap_mode") == "true") ? true : false;
        };
        if (server->hasArg("st_mode")) {
          GlobalValues::st_mode = (server->arg("st_mode") == "true") ? true : false;
        };
        if (server->hasArg("year") || server->hasArg("month") || server->hasArg("day") || server->hasArg("hour") || server->hasArg("minute") || server->hasArg("second")) {
          DateTime dt = EmuRTC::getSystemDateTime();
          int year = (server->arg("year").isEmpty()) ? dt.getYear() : server->arg("year").toInt();
          int month = (server->arg("month").isEmpty()) ? dt.getMonth() : server->arg("month").toInt();
          int day = (server->arg("day").isEmpty()) ? dt.getDay() : server->arg("day").toInt();
          int hour = (server->arg("hour").isEmpty()) ? dt.getHour() : server->arg("hour").toInt();
          int minute = (server->arg("minute").isEmpty()) ? dt.getMinute() : server->arg("minute").toInt();
          int second = (server->arg("second").isEmpty()) ? dt.getSecond() : server->arg("second").toInt();
          EmuRTC::setSystemDateTime(dt);
        };
      }
      if (callable == "clear_results") {
        if (GlobalValues::scanning) {
          GlobalValues::scan_results = "[]";
        }
      }
    } else {
      path = "/error";  // criar funcao functions aqui dentro dessa classe pra acessar o server
    };
    server->send(200, "text/html", WebPages::load(path, "Processing request..."));
  });

  server->on("/load", HTTP_GET, [server]() {
    String path = "/error";
    if (server->hasArg("path")) {
      path = server->arg("path");
    };
    server->send(200, "text/html", WebPages::load(path, "Loading control panel..."));
  });
}
