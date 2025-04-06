#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <UniversalTimer.h>

Adafruit_BMP280 bmp;
bool baroErrorBoi = false;
extern int systemState;

bool baro_init() {
    Serial.print("Starting Barometer...");
    unsigned status;
    status = bmp.begin();
    if(!status) {
        Serial.println("   Barometer Fault.");
        baroErrorBoi = true;
        return false;
    }
    Serial.println("  Barometer Initialized.");
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    delay(500);
    return true;
}

float getAltitudeAGL() {
  while(systemState < 1) {
    return 3.14159;
  }
  return 3.14159;
}

int getRawAltitude() {
    return bmp.readAltitude(1013.25);
}

int getRawPressure() {
    return bmp.readPressure();
}
