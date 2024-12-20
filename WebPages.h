#ifndef WebPages_h
#define WebPages_h

#include "GlobalValues.h"

#include <Arduino.h>
#include <EmuRTC.h>

class WebPages {
protected:
  WebPages();
  static String footer() {
    String html = "<footer style='body { font-family: 'Arial', sans-serif;";
    html += "color: #333; margin: 0; padding: 20px; text-align: center; font-size: 14px; }'>";
    html += "<br><br><br><div>WiFiScanner by DigitalFen - 2024</div></footer>";
    return html;
  };
public:
  static String admin();
  static String results();
  static String load(String path, String msg);
};

#endif
