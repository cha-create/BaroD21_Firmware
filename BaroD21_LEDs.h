#include <FastLED.h>

CRGB leds[4];


void fillLeds(CRGB color) {
  for(int i = 0; i < 4; i++) {
    leds[i] = color;
  }
  FastLED.show();
}

void clearLeds() {
  for(int i = 0; i < 4; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void slowFillLeds(CRGB color) {
  for(int i = 0; i < 4; i++) {
    leds[i] = color;
    FastLED.show();
    delay(350);
  }
}

void doubleFlashLeds(CRGB color) {
  fillLeds(color);
  delay(100);
  fillLeds(CRGB::Black);
  delay(75);
  fillLeds(color);
  delay(100);
  fillLeds(CRGB::Black);
  delay(150);
}

void leds_init() {
  FastLED.addLeds<NEOPIXEL, 0>(leds, 4);
  FastLED.setBrightness(15);
}

void statusLeds(int error, int code) {
  if(error) {
    doubleFlashLeds(CRGB::Red);
    switch(code) {
      case 1: // Barometer Failure
        leds[1] = CRGB::Red;
        leds[2] = CRGB::Green;
        FastLED.show();
        delay(500);
        break;
      case 2: // SD Failure
        leds[1] = CRGB::Green;
        leds[2] = CRGB::Red;
        FastLED.show();
        delay(500);
        break;
    }
    clearLeds();
    return;
  }
  doubleFlashLeds(CRGB::Green);
  clearLeds();
  delay(500);
  return;
}
