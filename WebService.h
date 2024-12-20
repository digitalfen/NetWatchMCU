#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <ESP8266WebServer.h>
#include "WebPages.h"

class WebService {
private:
  WebService();
public:
  static void registerDefaultRoutes(ESP8266WebServer* server);
};

#endif  // WEBSERVICE_H
