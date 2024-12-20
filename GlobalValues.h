#ifndef GLOBALVALUES_H
#define GLOBALVALUES_H

#include <Arduino.h>

class GlobalValues {
public:
  static unsigned long scan_repeat;
  static unsigned long scan_interval;
  static String scan_results;

  static String ap_ssid;
  static String ap_pwrd;
  static String st_ssid;
  static String st_pwrd;

  static bool scanning;
  static bool ap_mode;
  static bool st_mode;
};

#endif