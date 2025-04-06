#include "BaroD21_BMP280.h"
#include "BaroD21_LEDs.h"
#include "BaroD21_SD.h"
#define FIRMWARE_VERSION 1.1

extern bool baroErrorBoi;
extern bool SDErrorBoi;
int systemState = 0; // Main state machine
void setup() {
  Serial.begin(9600);
  delay(1000);
  leds_init();
  Serial.print("BaroD21 Firmware Version ");
  Serial.println(FIRMWARE_VERSION);
  delay(500);
  baro_init();
  SD_init();
  while(baroErrorBoi) {
    statusLeds(1, 1);
  }
  while(SDErrorBoi) {
    statusLeds(1, 2);
  }
  statusLeds(0, 0);
}

void loop() {
  datalog();
  int altitude = getRawAltitude();
  Serial.println(altitude);
  delay(100);
}
