#include "BaroD21_BMP280.h"
#include "BaroD21_LEDs.h"
#include "BaroD21_SD.h"
#define FIRMWARE_VERSION 1.1

int loopCount;
extern bool baroErrorBoi;
extern bool SDErrorBoi;
extern bool dataLogEnable;
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
  dataLogEnable = true;
}

void loop() {
  datalog();
  int altitude = getRawAltitude();
  Serial.print(altitude);

  delay(100);
  loopCount++;
  if(loopCount > 100) {
    systemState = 1;
    Serial.println("In Flight");
  }
  if(loopCount > 250) {
    dataLogEnable = false;
    Serial.println("Stopped Datalog");
  }
}
