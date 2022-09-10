/*

*/
#include "aht20.h"

//************************************************************************
//Constructor: Wire Lib öffnen

AHT20::AHT20() {
  Wire.begin();
  startuptime = millis();
}

AHT20::begin() {
  while (millis() - startuptime < 50) { delay(10); } 
}
