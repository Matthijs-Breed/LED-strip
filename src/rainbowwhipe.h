#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void RainbowWhipe(int times) {
  int size = 6;
  unsigned int colors[size] = {CRGB::Red, CRGB::OrangeRed, CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Purple};
  int dir = 1;
  int cc = 0;
  int i = 0;
  while (getMode() == m_RAINBOWWHIPE) {
    g_LEDs[i] = colors[cc];
    i += dir;
    if (i < 0 || i > NUM_LEDS) {
      cc = (cc + 1) % size;
      dir = -dir;
    }
    FastLED.show();

    EVERY_N_MILLISECONDS(500) {
      checkBrightness();
    }
  }  
  return;
}