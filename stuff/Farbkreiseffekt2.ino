#include <Adafruit_NeoPixel.h>
#define LED_PIN 3
#define LED_Count  71
int verzoegerung, farbsprung;

Adafruit_NeoPixel strip(LED_Count, LED_PIN, NEO_GRB + NEO_KHZ800);

struct colors {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class Farbkreiseffekt {
  private:
    colors Pixel_0;
    unsigned long timestamp;

  public:
    void set()  {
      timestamp = millis();
      Pixel_0.r = 255;
      Pixel_0.g = 0;
      Pixel_0.b = 0;
    }

    colors next_color(colors Farbe) {
      for (uint8_t Durchgaenge = 0; Durchgaenge < farbsprung; Durchgaenge++) {
        if (Farbe.r > 0 && Farbe.b == 0) { // Zustand 0
          Farbe.r--;
          Farbe.g++;
        }
        if (Farbe.g > 0 && Farbe.r == 0) { // Zustand 1
          Farbe.g--;
          Farbe.b++;
        }
        if (Farbe.b > 0 && Farbe.g == 0) { // Zustand 2
          Farbe.b--;
          Farbe.r++;
        }
      }
      return (Farbe);
    }

    uint8_t loop() {
      if (millis() >= timestamp + verzoegerung) {
        colors Pixelfarben = Pixel_0;
        for (int LED = 0; LED < LED_Count; LED++) {
          strip.setPixelColor(LED, Pixelfarben.r, Pixelfarben.g, Pixelfarben.b);
          Pixelfarben = next_color(Pixelfarben);
        }
        Pixel_0 = next_color(Pixel_0);
        strip.show();
        timestamp = millis();
      }
    }
};

Farbkreiseffekt Farbkreis;

void setup() {
Farbkreis.set();
}

void loop() {
  Farbkreis.loop();
}
