#include <Adafruit_NeoPixel.h>
#define led_count 110
#define LED_PIN 6 // Mega : 6    Pro: 3
Adafruit_NeoPixel strip(led_count, LED_PIN, NEO_GRB + NEO_KHZ800);
int spiral_red, spiral_blue, spiral_green, spiral_delay; // bei verzoegerung die selbe variable wie schon beim farbkreis benutzen; rotwert, blauwert, gruenwert, sind die Variablen, die der Benutzer einstellt, müssen also für die wc angepasst werden

class spiraleffekt
{

private:
  int spiral_i = 0, spiral_j = 0;
  bool spiral_geht_an = true, spiral_timestamp2_enabled = false, spiral_p = false;
  unsigned long timestamp, timestamp2;                                                                                                                                                                                                                                                                                                                                                                                                                                               //timestamp1 für Pausen zwischen den einzelnen LEDs, timestamp 2 für Pause zwsichen angehen und ausgehen
  uint8_t spiral_sr[110] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 21, 32, 43, 54, 65, 76, 87, 98, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 88, 77, 66, 55, 44, 33, 22, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 31, 42, 53, 64, 75, 86, 97, 96, 95, 94, 93, 92, 91, 90, 89, 78, 67, 56, 45, 34, 23, 24, 25, 26, 27, 28, 29, 30, 41, 52, 63, 74, 85, 84, 83, 82, 81, 80, 79, 68, 57, 46, 35, 36, 37, 38, 39, 40, 51, 62, 73, 72, 71, 70, 69, 58, 47, 48, 49, 50, 61, 60, 59}; // Alle LED's der Wordclock in der Reihenfolge, dass sie beim nacheinander abspielen eine Spirale ergeben

public:
  void set()
  {
    timestamp = millis();
    spiral_i = 0;
    spiral_j = 0;
  }

  uint8_t loop()
  {
    if (millis() > timestamp + spiral_delay)
    {
      if (spiral_geht_an)
      {
        if (spiral_j < led_count - 1)
        {
          strip.setPixelColor(spiral_sr[spiral_j], spiral_red, spiral_green, spiral_blue); //100,20,0 ist schönes braunrot
          spiral_j++;
        }
        else if (spiral_j == led_count - 1 && spiral_p == false && spiral_timestamp2_enabled == false)
        {
          spiral_p = true;
          strip.setPixelColor(spiral_sr[spiral_j], spiral_red, spiral_green, spiral_blue);
        }
        else if (spiral_j == led_count - 1 && spiral_p == true && spiral_timestamp2_enabled == false)
        {
          spiral_p = false;
          spiral_timestamp2_enabled = true;
        }
        else if (spiral_j == led_count - 1 && millis() > timestamp2 + spiral_delay)
        {
          spiral_geht_an = false;
          spiral_timestamp2_enabled = false;
        }
      }
      else
      {
        if (spiral_j > 0)
        {
          strip.setPixelColor(spiral_sr[spiral_j], 100, 2770, 0);
          spiral_j--;
        }
        else if (spiral_j == 0 && spiral_p == false && spiral_timestamp2_enabled == false)
        {
          spiral_p = true;
          strip.setPixelColor(spiral_sr[spiral_j], 100, 20, 0);
        }
        else if (spiral_j == 0 && spiral_p == true && spiral_timestamp2_enabled == false)
        {
          spiral_p = false;
          spiral_timestamp2_enabled = true;
        }
        else if (spiral_j == 0 && millis() > timestamp2 + spiral_delay)
        {
          spiral_geht_an = true;
          spiral_timestamp2_enabled = false;
        }
      }
      strip.show();
      timestamp = millis();
      if (spiral_timestamp2_enabled == true)
        timestamp2 = millis();
    }
  }
};

spiraleffekt spirale;

void setup()
{
  spirale.set();
}

void loop()
{
  spirale.loop();
}
