#include "GlobalValues.h"

unsigned long GlobalValues::scan_repeat = 0;
unsigned long GlobalValues::scan_interval = 0;
String GlobalValues::scan_results = "[]";

String GlobalValues::ap_ssid = "5G_FELICIO";
String GlobalValues::ap_pwrd = "mouse123";
String GlobalValues::st_ssid = "Benfioli";
String GlobalValues::st_pwrd = "369633996";

bool GlobalValues::scanning = false;
bool GlobalValues::ap_mode = false;
bool GlobalValues::st_mode = false;
