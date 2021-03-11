#include <Adafruit_NeoPixel.h>
#define LED_Count 110
#define LED_PIN 6 // Mega: 6    Pro: 3
Adafruit_NeoPixel strip(led_count, LED_PIN, NEO_GRB + NEO_KHZ800);

int rotwert, blauwert, gruenwert, verzoegerung;

class explosionseffekt
{
private:
  int explosion_i, explosion_j, explosion_b;
  bool explosion_geht_an = true, explosion_timestamp2_enabled = false, explosion_p = false;
  unsigned long timestamp, timestamp2;

public:
  void set()
  {
    timestamp = millis();
    timestamp2 = millis();
    explosion_i = 0;
    explosion_j = 0;
    explosion_b = 0;
  }
  void loop()
  {
    if (millis() > timestamp + verzoegerung)
    {
      if (explosion_geht_an)
      {
        if (explosion_j < 5)
        {
          for (int b = 1 + 12 * explosion_j; b <= 9 + 10 * explosion_j; b++)
            strip.setPixelColor(b, rotwert, gruenwert, blauwert);
          for (int b = 100 - 10 * explosion_j; b <= 108 - 12 * explosion_j; b++)
            strip.setPixelColor(b, rotwert, gruenwert, blauwert);
          for (int b = 12 * explosion_j; b <= 99 - 10 * explosion_j; b += 11)
            strip.setPixelColor(b, rotwert, gruenwert, blauwert);
          for (int b = 10 + 10 * explosion_j; b <= 109 - 12 * explosion_j; b += 11)
            strip.setPixelColor(b, rotwert, gruenwert, blauwert);
          if (explosion_j == 4 && !explosion_p)
          {
            explosion_timestamp2_enabled = true;
            explosion_p = true;
          }
          if (explosion_j == 4 && millis() > timestamp2 + verzoegerung)
          {
            explosion_geht_an = false;
            explosion_p = false;
          }
          if (explosion_j < 4)
            explosion_j++;
        }
      }
      else
      {
        if (explosion_j >= 0)
        {
          for (int b = 1 + 12 * explosion_j; b <= 9 + 10 * explosion_j; b++)
            strip.setPixelColor(b, 0, 0, 0);
          for (int b = 100 - 10 * explosion_j; b <= 108 - 12 * explosion_j; b++)
            strip.setPixelColor(b, 0, 0, 0);
          for (int b = 12 * explosion_j; b <= 99 - 10 * explosion_j; b += 11)
            strip.setPixelColor(b, 0, 0, 0);
          for (int b = 10 + 10 * explosion_j; b <= 109 - 12 * explosion_j; b += 11)
            strip.setPixelColor(b, 0, 0, 0);
          if (explosion_j == 0 && !explosion_p)
          {
            explosion_timestamp2_enabled = true;
            explosion_p = true;
          }
          if (explosion_j == 0 && millis() > timestamp2 + verzoegerung)
          {
            explosion_geht_an = true;
            explosion_p = false;
          }
          if (explosion_j > 0)
            explosion_j--;
        }
      }
      timestamp = millis();
      if (explosion_timestamp2_enabled)
      {
        timestamp2 = millis();
        explosion_timestamp2_enabled = false;
      }
    }
  }
};

explosionseffekt explosion;

void setup()
{
  explosion.set();
}

void loop()
{
  explosion.loop();
}
