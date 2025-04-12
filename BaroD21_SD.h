#include <SD.h>

File output;
bool SDErrorBoi = false;
bool dataLogEnable = false;
const char filename[] = "dataLog.txt";
extern int altitude;
char buffer[128];
bool hasRun = false;

bool SD_init() {
  Serial.print("Starting SD Card...");
  if(!SD.begin(2)) {  // Change CS Pin!!
      Serial.println("  SD Card Fault.");
      SDErrorBoi = true;
      return false;
   }
   Serial.println("  SD Initialized.");
   delay(500);

   if(SD.exists(filename)) {
    SD.remove(filename);
   }
   output = SD.open(filename, FILE_WRITE);
   if(!hasRun) {
     if(output) {
        output.println("Time, rawAltitude, altitudeAGL");
     }
     hasRun = true;
   }
   output.close();
   return true;
}

void datalog() {
  output = SD.open(filename, FILE_WRITE);
  char floatBuf[16];
  if(output && dataLogEnable) {
    Serial.println("Logging");
    // dtostrf(getAltitudeAGL(), 6, 2, floatBuf); // Because sprintf doesn't support floats
    // sprintf(buffer, "%d, %d, %f,", millis(), getRawAltitude(), floatBuf);
    // output.println(buffer);
    output.print(millis());
    output.print(", ");
    output.print(getRawAltitude());
    output.print(", ");
    output.print(getAltitudeAGL(), 2);  // 2 decimal places
    output.println(", ");
    output.close();
    delay(10);
  }
}
