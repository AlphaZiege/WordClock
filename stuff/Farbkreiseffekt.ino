#include <Adafruit_NeoPixel.h>
#define LED_PIN 3
#define LED_Count 71
int verzoegerung, farbsprung;

Adafruit_NeoPixel strip(LED_Count, LED_PIN, NEO_GRB + NEO_KHZ800);

struct colors
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class Farbkreiseffekt
{
private:
  colors Pixel_0;
  unsigned long timestamp;
  String Line[4];
  uint8_t ESC, Eigene_Menuenummer;

public:
  void set(uint8_t Stern, uint8_t eigene_Arraynummer)
  {
    ESC = Stern;
    Eigene_Menuenummer = eigene_Arraynummer;
    timestamp = millis();
    Pixel_0.r = 255;
    Pixel_0.g = 0;
    Pixel_0.b = 0;
  }

  uint8_t loop()
  {
    if (millis() >= timestamp + verzoegerung)
    {
      colors Pixelfarben = Pixel_0;
      for (int LED = 0; LED < LED_Count; LED++)
      {
        strip.setPixelColor(LED, Pixelfarben.r, Pixelfarben.g, Pixelfarben.b);
        for (uint8_t Durchgaenge = 0; Durchgaenge < farbsprung; Durchgaenge++)
        {
          if (Pixelfarben.r > 0 && Pixelfarben.b == 0)
          { // Zustand 0
            Pixelfarben.r--;
            Pixelfarben.g++;
          }
          if (Pixelfarben.g > 0 && Pixelfarben.r == 0)
          { // Zustand 1
            Pixelfarben.g--;
            Pixelfarben.b++;
          }
          if (Pixelfarben.b > 0 && Pixelfarben.g == 0)
          { // Zustand 2
            Pixelfarben.b--;
            Pixelfarben.r++;
          }
          if (Pixelfarben.r == 0 && Pixelfarben.g == 0 && Pixelfarben.b == 0)
          {
            Pixelfarben.r = 255;
          }
        }
      }
      for (uint8_t Durchgaenge = 0; Durchgaenge < farbsprung; Durchgaenge++)
      {
        if (Pixel_0.r > 0 && Pixel_0.b == 0)
        { // Zustand 0
          Pixel_0.r--;
          Pixel_0.g++;
        }
        if (Pixel_0.g > 0 && Pixel_0.r == 0)
        { // Zustand 1
          Pixel_0.g--;
          Pixel_0.b++;
        }
        if (Pixel_0.b > 0 && Pixel_0.g == 0)
        { // Zustand 2
          Pixel_0.b--;
          Pixel_0.r++;
        }
        if (Pixel_0.r == 0 && Pixel_0.g == 0 && Pixel_0.b == 0)
          {
            Pixel_0.r = 255;
          }
      }
      strip.show();
      timestamp = millis();
    }
  }
};

Farbkreiseffekt Farbkreis;

void setup()
{
}

void loop()
{
  Farbkreis.loop();
}
