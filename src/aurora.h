#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

// https://cssgradient.io/
DEFINE_GRADIENT_PALETTE(aurora_pallete) {
0,0,255,100,
20,0,207,170,
80,0,0,255,
127,0,0,255,
150,0,0,255,
180,0,224,255,
255,244,0,255
};

int modulo(int value, int base)
{
  return abs(value % base);
}

void Aurora()
{
  FastLED.clear();
  CRGBPalette16 auroraPallete = aurora_pallete;
  int lights_0[NUM_LEDS] = {0};
  int lights_1[NUM_LEDS] = {0};
  float phase = ( 2 * PI ) / ( NUM_LEDS );
  for (int i = 0; i < NUM_LEDS ; i++) {
    lights_0[i] = (int)(255 * sin(i * phase * 2) + 127);
    lights_1[i] = (int)(255 * sin((i + 32) * phase) + 127);
  }
  int j = 0;

  while (getMode() == m_AURORA)
  {
    EVERY_N_MILLISECONDS(200) {
      for (int i = 0; i < NUM_LEDS ; i++) {
        g_LEDs[i] = ColorFromPalette(
          auroraPallete,
           lights_0[modulo((i + j), NUM_LEDS)] / 3 +
           lights_0[modulo((-i + j * 2), NUM_LEDS)] / 3 +
           lights_1[modulo((i + j), NUM_LEDS)] / 3 
        );
      }
      j++;
      
      FastLED.show();
    }
  }
  EVERY_N_MILLISECONDS(500) {
  checkBrightness();
  }
}