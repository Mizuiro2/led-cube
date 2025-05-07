#include <Adafruit_NeoPixel.h>

#define LED_PIN     5         // Use a safe GPIO like 5, 13, 14, 18, 23
#define NUM_LEDS    512       // Or however many LEDs you have
#define BRIGHTNESS  80        // Lower if you’re testing power limits

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all LEDs to OFF
  delay(1000);
}

void loop() {
  // Red
  fillColor(strip.Color(255, 0, 0));
  delay(1000);

  // Green
  fillColor(strip.Color(0, 255, 0));
  delay(1000);

  // Blue
  fillColor(strip.Color(0, 0, 255));
  delay(1000);

  // Rainbow test
  rainbowCycle(5);
}

// Fill entire panel with one color
void fillColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

// Smooth rainbow test
void rainbowCycle(uint8_t wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}
