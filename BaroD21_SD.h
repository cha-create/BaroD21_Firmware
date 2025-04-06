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
        output.println("Time, Altitude");
     }
     hasRun = true;
   }
   output.close();
   return true;
}

void datalog() {
  output = SD.open(filename, FILE_WRITE);
  if(output && dataLogEnable) {
    sprintf(buffer, "%d, %d");
    output.println(buffer);
    delay(10);
  }
  else {
    output.close();
  }
}
