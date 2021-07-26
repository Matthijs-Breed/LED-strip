#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];
extern int brightness;

void Pulse()
{
    FastLED.clear();
    uint8_t hue;
    uint8_t x;
    int t;

    while (getMode() == m_PULSE)
    {
        x = 0;
        t = 0;
        float phase = ( 2 * PI ) / ( 50 );
        EVERY_N_MILLISECONDS(20) {
            hue = inoise8(t + x, millis() / 10);
            for (int i = 0; i < NUM_LEDS; i++) {
                g_LEDs[i].setHue(hue);
            }
            t++;
            FastLED.setBrightness(50 * sin(t * phase) + 25);
            FastLED.show();
        }
    }
}