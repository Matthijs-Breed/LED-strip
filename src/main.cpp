#include <Arduino.h>
#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <time.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define OLED_RESET  16
#define OLED_CLOCK  15
#define OLED_DATA   4

#define NUM_LEDS    300
#define LED_PIN     5

const int m_MARQUEE       = 1;
const int m_RAINBOWWHIPE  = 2;
const int m_TWINKLE       = 3;
const int m_RAINBOWWAVE   = 4;
const int m_POPI          = 5;
const int m_COLOR_SLIDER  = 6;
const int m_COMET         = 7;
const int m_AURORA        = 8;
const int m_LAVA          = 9;

clock_t t_Cache;
int mode;
clock_t b_Cache;
clock_t twinkle_Cache;
int brightness;
unsigned int slider_color;
CRGB g_LEDs[NUM_LEDS] = {0};

U8G2_SSD1306_128X64_NONAME_F_HW_I2C   u8g2(U8G2_R0, 16, 15, 4);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R0, OLED_RESET, OLED_CLOCK, OLED_DATA);
int g_lineHeight = 0;

const char* ssid = "Ultimate Internet";
const char* password = "eikenhof";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);
  FastLED.setBrightness(10);

  // Initialize display
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  // Buffer for text
  char chBuffer[128];

  // Connect to WiFi
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    sprintf(chBuffer, "Connecting to WiFi..");
    u8g2.drawStr(0, 0, chBuffer);
    u8g2.sendBuffer();
  }
}

#include "update.h"
#include "marquee.h"
#include "rainbowwhipe.h"
#include "twinkle.h"
#include "rainbowwave.h"
#include "popi.h"
#include "colorslider.h"
#include "comets.h"
#include "aurora.h"
#include "lava.h"

void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( g_LEDs[pixelnumber], newcolor, 64);
  }
  FastLED.show();
}

void loop() {
  FastLED.clear();
  checkBrightness();
  
  int mode = getMode();
  switch (mode) {
    case m_MARQUEE :
      MarqueeRainbow();
      break;
    case m_RAINBOWWHIPE:
      RainbowWhipe(1);
      break;
    case m_TWINKLE:
      Twinkle(60);
      break;
    case m_RAINBOWWAVE:
      RainbowWave();
      break;
    case m_POPI:
      PoPi();
      break;
    case m_COLOR_SLIDER:
      ColorSlider();
      break;
    case m_COMET:
      DrawComet();
      break;
    case m_AURORA:
      Aurora();
      break;
    case m_LAVA:
      Lava();
      break;
    default:
      FastLED.clear(true);
  }
}