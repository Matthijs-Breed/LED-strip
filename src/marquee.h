#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void MarqueeRainbow() {
  unsigned int colors[6] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Green, CRGB::Blue, CRGB::Purple};
  int iterator = 0;

  while (getMode() == m_MARQUEE) {
    EVERY_N_MILLISECONDS(50) 
    {
      for (int i = 0; i < NUM_LEDS; i++)
        {
          g_LEDs[i] = colors[(i + iterator) % 6];
        }
      for (int b = (iterator % 10); b < NUM_LEDS; b += 10)
        {
          g_LEDs[b] = CRGB::Black;
        }    
      iterator++;
      FastLED.show();
    }
    EVERY_N_MILLISECONDS(500) {
      checkBrightness();
    }
  }
  return;
}