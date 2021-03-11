#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>

#define DCF_Pin 14
// Es folgen drei Zustände für die Variable Zustand:
#define wait_for_DCF 0
#define synchronisiere 1
#define ok 2

#define punkt12 "11011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111100000000111";
#define a5nach12 "11011101111000000011110000000000000000000000000000000000000000000000000000000000000000000000001111100000000000";
#define a10nach12 "11011100000111100011110000000000000000000000000000000000000000000000000000000000000000000000001111100000000000";
#define a15nach12 "11011101111111100011110000000000000000000000000000000000000000000000000000000000000000000000001111100000000000";
#define a15timo12 "11011100000000000000000001111111000000000000000000000001111000000000000000000000000000000000000000000000000000";
#define a20nach12 "11011100000111100000000000000000001110001111000000000001111000000000000000000000000000000000000000000000000000";
#define a25nach12 "11011101111000000000000000000000001110001111000000000001111000000000000000000000000000000000000000000000000000";
#define a30nach12 "11011100000000000000000000000000000000001111000000000001111000000000000000000000000000000000000000000000000000";
#define a35nach12 "11011101111000000011110000000000000000001111000000000001111000000000000000000000000000000000000000000000000000";
#define a40nach12 "11011101111000000011110000000000000000001111000000000001111000000000000000000000000000000000000000000000000000";
#define a45nach12 "11011100000000000000000001111111001110000000000000000001111000000000000000000000000000000000000000000000000000";
#define a50nach12 "11011100000111100000000000000000001110000000000000000001111000000000000000000000000000000000000000000000000000";
#define a55nach12 "11011101111000000000000000000000001110000000000000000001111000000000000000000000000000000000000000000000000000";

#define punkt1 "11011100000000000000000000000000000000000000000000000001110000000000000000000000000000000000000000000000000111";
#define a5nach1 "11011101111000000011110000000000000000000000000000000001111000000000000000000000000000000000000000000000000000";
#define a10nach1 "11011100000111100011110000000000000000000000000000000001111000000000000000000000000000000000000000000000000000";
#define a15nach1 "11011101111111100011110000000000000000000000000000000001111000000000000000000000000000000000000000000000000000";
#define a20nach1 "11011100000111100000000000000000001110001111000000000000000000111100000000000000000000000000000000000000000000";
#define a25nach1 "11011101111000000000000000000000001110001111000000000000000000111100000000000000000000000000000000000000000000";
#define a30nach1 "11011100000000000000000000000000000000001111000000000000000000111100000000000000000000000000000000000000000000";
#define a35nach1 "11011101111000000011110000000000000000001111000000000000000000111100000000000000000000000000000000000000000000";
#define a40nach1 "11011100000111100011110000000000000000001111000000000000000000111100000000000000000000000000000000000000000000";
#define a45nach1 "11011100000000000000000001111111001110000000000000000000000000111100000000000000000000000000000000000000000000";
#define a50nach1 "11011100000111100000000000000000001110000000000000000000000000111100000000000000000000000000000000000000000000";
#define a55nach1 "11011101111000000000000000000000001110000000000000000000000000111100000000000000000000000000000000000000000000";

#define punkt2 "11011100000000000000000000000000000000000000000000000000000000111100000000000000000000000000000000000000000111";
#define a5nach2 "11011101111000000011110000000000000000000000000000000000000000111100000000000000000000000000000000000000000000";
#define a10nach2 "11011100000111100011110000000000000000000000000000000000000000111100000000000000000000000000000000000000000000";
#define a15nach2 "11011101111111100011110000000000000000000000000000000000000000111100000000000000000000000000000000000000000000";
#define a20nach2 "11011100000111100000000000000000001110001111000000000000000000000011110000000000000000000000000000000000000000";
#define a25nach2 "11011101111000000000000000000000001110001111000000000000000000000011110000000000000000000000000000000000000000";
#define a30nach2 "11011100000000000000000000000000000000001111000000000000000000000011110000000000000000000000000000000000000000";
#define a35nach2 "11011101111000000011110000000000000000001111000000000000000000000011110000000000000000000000000000000000000000";
#define a40nach2 "11011100000111100011110000000000000000001111000000000000000000000011110000000000000000000000000000000000000000";
#define a45nach2 "11011100000000000000000001111111001110000000000000000000000000000011110000000000000000000000000000000000000000";
#define a50nach2 "11011100000111100000000000000000001110000000000000000000000000000011110000000000000000000000000000000000000000";
#define a55nach2 "11011101111000000000000000000000001110000000000000000000000000000011110000000000000000000000000000000000000000";

#define punkt3 "11011100000000000000000000000000000000000000000000000000000000000011110000000000000000000000000000000000000111";
#define a5nach3 "11011101111000000011110000000000000000000000000000000000000000000011110000000000000000000000000000000000000000";
#define a10nach3 "11011100000111100011110000000000000000000000000000000000000000000011110000000000000000000000000000000000000000";
#define a15nach3 "11011101111111100011110000000000000000000000000000000000000000000011110000000000000000000000000000000000000000";
#define a20nach3 "11011100000111100000000000000000001110001111000000000000000000000000000001111000000000000000000000000000000000";
#define a25nach3 "11011101111000000000000000000000001110001111000000000000000000000000000001111000000000000000000000000000000000";
#define a30nach3 "11011100000000000000000000000000000000001111000000000000000000000000000001111000000000000000000000000000000000";
#define a35nach3 "11011101111000000011110000000000000000001111000000000000000000000000000001111000000000000000000000000000000000";
#define a40nach3 "11011100000111100011110000000000000000001111000000000000000000000000000001111000000000000000000000000000000000";
#define a45nach3 "11011100000000000000000001111111001110000000000000000000000000000000000001111000000000000000000000000000000000";
#define a50nach3 "11011100000111100000000000000000001110000000000000000000000000000000000001111000000000000000000000000000000000";
#define a55nach3 "11011101111000000000000000000000001110000000000000000000000000000000000001111000000000000000000000000000000000";

#define punkt4 "11011100000000000000000000000000000000000000000000000000000000000000000001111000000000000000000000000000000111";
#define a5nach4 "11011101111000000011110000000000000000000000000000000000000000000000000001111000000000000000000000000000000000";
#define a10nach4 "11011100000111100011110000000000000000000000000000000000000000000000000001111000000000000000000000000000000000";
#define a15nach4 "11011101111111100011110000000000000000000000000000000000000000000000000001111000000000000000000000000000000000";
#define a20nach4 "11011100000111100000000000000000001110001111000000011110000000000000000000000000000000000000000000000000000000";
#define a25nach4 "11011101111000000000000000000000001110001111000000011110000000000000000000000000000000000000000000000000000000";
#define a30nach4 "11011100000000000000000000000000000000001111000000011110000000000000000000000000000000000000000000000000000000";
#define a35nach4 "11011101111000000011110000000000000000001111000000011110000000000000000000000000000000000000000000000000000000";
#define a40nach4 "11011100000111100011110000000000000000001111000000011110000000000000000000000000000000000000000000000000000000";
#define a45nach4 "11011100000000000000000001111111001110000000000000011110000000000000000000000000000000000000000000000000000000";
#define a50nach4 "11011100000111100000000000000000001110000000000000011110000000000000000000000000000000000000000000000000000000";
#define a55nach4 "11011101111000000000000000000000001110000000000000011110000000000000000000000000000000000000000000000000000000";

#define punkt5 "11011100000000000000000000000000000000000000000000011110000000000000000000000000000000000000000000000000000111";
#define a5nach5 "11011101111000000011110000000000000000000000000000011110000000000000000000000000000000000000000000000000000000";
#define a10nach5 "11011100000111100011110000000000000000000000000000011110000000000000000000000000000000000000000000000000000000";
#define a15nach5 "11011101111111100011110000000000000000000000000000011110000000000000000000000000000000000000000000000000000000";
#define a20nach5 "11011100000111100000000000000000001110001111000000000000000000000000000000000111110000000000000000000000000000";
#define a25nach5 "11011101111000000000000000000000001110001111000000000000000000000000000000000111110000000000000000000000000000";
#define a30nach5 "11011100000000000000000000000000000000001111000000000000000000000000000000000111110000000000000000000000000000";
#define a35nach5 "11011101111000000011110000000000000000001111000000000000000000000000000000000111110000000000000000000000000000";
#define a40nach5 "11011100000111100011110000000000000000001111000000000000000000000000000000000111110000000000000000000000000000";
#define a45nach5 "11011100000000000000000001111111001110000000000000000000000000000000000000000111110000000000000000000000000000";
#define a50nach5 "11011100000111100000000000000000001110000000000000000000000000000000000000000111110000000000000000000000000000";
#define a55nach5 "11011101111000000000000000000000001110000000000000000000000000000000000000000111110000000000000000000000000000";

#define punkt6 "11011100000000000000000000000000000000000000000000000000000000000000000000000111110000000000000000000000000111";
#define a5nach6 "11011101111000000011110000000000000000000000000000000000000000000000000000000111110000000000000000000000000000";
#define a10nach6 "11011100000111100011110000000000000000000000000000000000000000000000000000000111110000000000000000000000000000";
#define a15nach6 "11011101111111100011110000000000000000000000000000000000000000000000000000000111110000000000000000000000000000";
#define a20nach6 "11011100000111100000000000000000001110001111000000000000000000000000000000000000000000001111110000000000000000";
#define a25nach6 "11011101111000000000000000000000001110001111000000000000000000000000000000000000000000001111110000000000000000";
#define a30nach6 "11011100000000000000000000000000000000001111000000000000000000000000000000000000000000001111110000000000000000";
#define a35nach6 "11011101111000000011110000000000000000001111000000000000000000000000000000000000000000001111110000000000000000";
#define a40nach6 "11011100000111100011110000000000000000001111000000000000000000000000000000000000000000001111110000000000000000";
#define a45nach6 "11011100000000000000000001111111001110000000000000000000000000000000000000000000000000001111110000000000000000";
#define a50nach6 "11011100000111100000000000000000001110000000000000000000000000000000000000000000000000001111110000000000000000";
#define a55nach6 "11011101111000000000000000000000001110000000000000000000000000000000000000000000000000001111110000000000000000";

#define punkt7 "11011100000000000000000000000000000000000000000000000000000000000000000000000000000000001111110000000000000111";
#define a5nach7 "11011101111000000011110000000000000000000000000000000000000000000000000000000000000000001111110000000000000000";
#define a10nach7 "11011100000111100011110000000000000000000000000000000000000000000000000000000000000000001111110000000000000000";
#define a15nach7 "11011101111111100011110000000000000000000000000000000000000000000000000000000000000000001111110000000000000000";
#define a20nach7 "11011100000111100000000000000000001110001111000000000000000000000000000000000000000011110000000000000000000000";
#define a25nach7 "11011101111000000000000000000000001110001111000000000000000000000000000000000000000011110000000000000000000000";
#define a30nach7 "11011100000000000000000000000000000000001111000000000000000000000000000000000000000011110000000000000000000000";
#define a35nach7 "11011101111000000011110000000000000000001111000000000000000000000000000000000000000011110000000000000000000000";
#define a40nach7 "11011100000111100011110000000000000000001111000000000000000000000000000000000000000011110000000000000000000000";
#define a45nach7 "11011100000000000000000001111111001110000000000000000000000000000000000000000000000011110000000000000000000000";
#define a50nach7 "11011100000111100000000000000000001110000000000000000000000000000000000000000000000011110000000000000000000000";
#define a55nach7 "11011101111000000000000000000000001110000000000000000000000000000000000000000000000011110000000000000000000000";

#define punkt8 "11011100000000000000000000000000000000000000000000000000000000000000000000000000000011110000000000000000000111";
#define a5nach8 "11011101111000000011110000000000000000000000000000000000000000000000000000000000000011110000000000000000000000";
#define a10nach8 "11011100000111100011110000000000000000000000000000000000000000000000000000000000000011110000000000000000000000";
#define a15nach8 "11011101111111100011110000000000000000000000000000000000000000000000000000000000000011110000000000000000000000";
#define a20nach8 "11011100000111100000000000000000001110001111111100000000000000000000000000000000000000000000000000000000000000";
#define a25nach8 "11011101111000000000000000000000001110001111111100000000000000000000000000000000000000000000000000000000000000";
#define a30nach8 "11011100000000000000000000000000000000001111111100000000000000000000000000000000000000000000000000000000000000";
#define a35nach8 "11011101111000000011110000000000000000001111111100000000000000000000000000000000000000000000000000000000000000";
#define a40nach8 "11011100000111100011110000000000000000001111111100000000000000000000000000000000000000000000000000000000000000";
#define a45nach8 "11011100000000000000000001111111001110000000111100000000000000000000000000000000000000000000000000000000000000";
#define a50nach8 "11011100000111100000000000000000001110000000111100000000000000000000000000000000000000000000000000000000000000";
#define a55nach8 "11011101111000000000000000000000001110000000111100000000000000000000000000000000000000000000000000000000000000";

#define punkt9 "11011100000000000000000000000000000000000000111100000000000000000000000000000000000000000000000000000000000111";
#define a5nach9 "11011101111000000011110000000000000000000000111100000000000000000000000000000000000000000000000000000000000000";
#define a10nach9 "11011100000111100011110000000000000000000000111100000000000000000000000000000000000000000000000000000000000000";
#define a15nach9 "11011101111111100011110000000000000000000000111100000000000000000000000000000000000000000000000000000000000000";
#define a20nach9 "11011100000111100000000000000000001110001111000000000000000000000000000000000000000000000000000000011110000000";
#define a25nach9 "11011101111000000000000000000000001110001111000000000000000000000000000000000000000000000000000000011110000000";
#define a30nach9 "11011100000000000000000000000000000000001111000000000000000000000000000000000000000000000000000000011110000000";
#define a35nach9 "11011101111000000011110000000000000000001111000000000000000000000000000000000000000000000000000000011110000000";
#define a40nach9 "11011100000111100011110000000000000000001111000000000000000000000000000000000000000000000000000000011110000000";
#define a45nach9 "11011100000000000000000001111111001110000000000000000000000000000000000000000000000000000000000000011110000000";
#define a50nach9 "11011100000111100000000000000000001110000000000000000000000000000000000000000000000000000000000000011110000000";
#define a55nach9 "11011101111000000000000000000000001110000000000000000000000000000000000000000000000000000000000000011110000000";

#define punkt10 "11011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011110000111";
#define a5nach10 "11011101111000000011110000000000000000000000000000000000000000000000000000000000000000000000000000011110000000";
#define a10nach10 "11011100000111100011110000000000000000000000000000000000000000000000000000000000000000000000000000011110000000";
#define a15nach10 "11011101111111100011110000000000000000000000000000000000000000000000000000000000000000000000000000011110000000";
#define a20nach10 "11011100000111100000000000000000001110001111000000000000000000000000000000000000000000000000000000000001110000";
#define a25nach10 "11011101111000000000000000000000001110001111000000000000000000000000000000000000000000000000000000000001110000";
#define a30nach10 "11011100000000000000000000000000000000001111000000000000000000000000000000000000000000000000000000000001110000";
#define a35nach10 "11011101111000000011110000000000000000001111000000000000000000000000000000000000000000000000000000000001110000";
#define a40nach10 "11011100000111100011110000000000000000001111000000000000000000000000000000000000000000000000000000000001110000";
#define a45nach10 "11011100000000000000000001111111001110000000000000000000000000000000000000000000000000000000000000000001110000";
#define a50nach10 "11011100000111100000000000000000001110000000000000000000000000000000000000000000000000000000000000000001110000";
#define a55nach10 "11011101111000000000000000000000001110000000000000000000000000000000000000000000000000000000000000000001110000";

#define punkt11 "11011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001110111";
#define a5nach11 "11011101111000000011110000000000000000000000000000000000000000000000000000000000000000000000000000000001110000";
#define a10nach11 "11011100000111100011110000000000000000000000000000000000000000000000000000000000000000000000000000000001110000";
#define a15nach11 "11011101111111100011110000000000000000000000000000000000000000000000000000000000000000000000000000000001110000";
#define a20nach11 "11011100000111100000000000000000001110001111000000000000000000000000000000000000000000000000001111100000000000";
#define a25nach11 "11011101111000000000000000000000001110001111000000000000000000000000000000000000000000000000001111100000000000";
#define a30nach11 "11011100000000000000000000000000000000001111000000000000000000000000000000000000000000000000001111100000000000";
#define a35nach11 "11011101111000000011110000000000000000001111000000000000000000000000000000000000000000000000001111100000000000";
#define a40nach11 "11011100000111100011110000000000000000001111000000000000000000000000000000000000000000000000001111100000000000";
#define a45nach11 "11011100000000000000000001111111001110000000000000000000000000000000000000000000000000000000001111100000000000";
#define a50nach11 "11011100000111100000000000000000001110000000000000000000000000000000000000000000000000000000001111100000000000";
#define a55nach11 "11011101111000000000000000000000001110000000000000000000000000000000000000000000000000000000001111100000000000";

// Wlan Zugang
const char *ssid = "WLAN";
const char *password = "kevin123";

const int DATA_PIN = D3; //LED-Pin
const int len_x = 11;
const int len_y = 10;
const int led_count = len_x * len_y;
unsigned long timestamp;
bool fade_in = true;

int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];
int breathe_index = 0;

Adafruit_NeoPixel strip(led_count, DATA_PIN, NEO_GRB + NEO_KHZ800); // leds init

struct colors
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

colors Pixel_0 = colors();

class Zeit
{
private:
  String weather;
  int zeitsystem = 0, minutes = 30, hours = 1, dayMonth = 0, dayWeek = 0, month = 0, calendarYear = 0;

public:
  void set_weather(String yes)
  {
    weather = yes;
  }
  String get_weather()
  {
    return weather;
  }
  void set_zeitsystem(int yes)
  {
    zeitsystem = yes;
  }
  int get_zeitsystem()
  {
    return zeitsystem;
  }
  void set_minutes(int yes)
  {
    minutes = yes;
  }
  int get_minutes()
  {
    return minutes;
  }
  void set_hours(int yes)
  {
    hours = yes;
  }
  int get_hours()
  {
    return hours;
  }
  void set_dayMonth(int yes)
  {
    dayMonth = yes;
  }
  int get_dayMonth()
  {
    return dayMonth;
  }
  void set_dayWeek(int yes)
  {
    dayWeek = yes;
  }
  int get_dayWeek()
  {
    return dayWeek;
  }
  void set_month(int yes)
  {
    month = yes;
  }
  int get_month()
  {
    return month;
  }
  void set_calendarYear(int yes)
  {
    calendarYear = yes;
  }
  int get_calendarYear()
  {
    return calendarYear;
  }

  String update()
  {
    switch (hours)
    {
    case 1:
      if (minutes <= 3)
      {
        return punkt1;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach1;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach1;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach1;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach1;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach1;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach1;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach1;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach1;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach1;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach1;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach1;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt2;
      }
      break;

    case 2:
      if (minutes <= 3)
      {
        return punkt2;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach2;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach2;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach2;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach2;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach2;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach2;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach2;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach2;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach2;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach2;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach2;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt3;
      }
      break;

    case 3:
      if (minutes <= 3)
      {
        return punkt3;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach3;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach3;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach3;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach3;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach3;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach3;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach3;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach3;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach3;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach3;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach3;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt4; 
      }    
      break;

    case 4:
      if (minutes <= 3)
      {
        return punkt4;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach4;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach4;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach4;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach4;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach4;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach4;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach4;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach4;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach4;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach4;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach4;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt5; 
      }    
      break;

      case 5:
      if (minutes <= 3)
      {
        return punkt5;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach5;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach5;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach5;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach5;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach5;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach5;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach5;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach5;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach5;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach5;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach5;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt6; 
      }    
      break;

      case 6:
      if (minutes <= 3)
      {
        return punkt6;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach6;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach6;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach6;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach6;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach6;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach6;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach6;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach6;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach6;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach6;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach6;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt7; 
      }    
      break;

      case 7:
      if (minutes <= 3)
      {
        return punkt7;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach7;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach7;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach7;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach7;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach7;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach7;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach7;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach7;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach7;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach7;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach7;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt8; 
      }    
      break;

      case 8:
      if (minutes <= 3)
      {
        return punkt8;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach8;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach8;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach8;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach8;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach8;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach8;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach8;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach8;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach8;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach8;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach8;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt9; 
      }    
      break;

      case 9:
      if (minutes <= 3)
      {
        return punkt9;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach9;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach9;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach9;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach9;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach9;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach9;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach9;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach9;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach9;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach9;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach9;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt10;
      }    
      break;

      case 10:
      if (minutes <= 3)
      {
        return punkt10;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach10;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach10;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach10;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach10;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach10;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach10;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach10;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach10;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach10;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach10;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach10;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt11; 
      }    
      break;

      case 11:
      if (minutes <= 3)
      {
        return punkt11;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach11;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach11;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach11;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach11;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach11;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach11;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach11;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach11;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach11;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach11;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach11;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt12; 
      }    
      break;

      case 12:
      if (minutes <= 3)
      {
        return punkt12;
      }
      else if (minutes > 3 && minutes <= 8)
      {
        return a5nach12;
      }
      else if (minutes > 8 && minutes <= 13)
      {
        return a10nach12;
      }
      else if (minutes > 13 && minutes <= 18)
      {
        return a15nach12;
      }
      else if (minutes > 18 && minutes <= 23)
      {
        return a20nach12;
      }
      else if (minutes > 23 && minutes <= 28)
      {
        return a25nach12;
      }
      else if (minutes > 28 && minutes <= 33)
      {
        return a30nach12;
      }
      else if (minutes > 33 && minutes <= 38)
      {
        return a35nach12;
      }
      else if (minutes > 38 && minutes <= 43)
      {
        return a40nach12;
      }
      else if (minutes > 43 && minutes <= 48)
      {
        return a45nach12;
      }
      else if (minutes > 48 && minutes <= 53)
      {
        return a50nach12;
      }
      else if (minutes > 53 && minutes <= 58)
      {
        return a55nach12;
      }
      else if (minutes > 58 && minutes <= 63)
      {
        return punkt1; 
      }    
      break;
    }
  }
};

class ColorScheme
{
private:
  bool staticColor, fadeColor, randomColor;
  bool randomColorStatic, randomColorTimer;
  int SC_RED = 0, SC_GREEN = 0, SC_BLUE = 0;

public:
  void update()
  {
    strip.setBrightness(200);
  }
  //modes
  void set_staticColor(bool yes)
  {
    staticColor = yes;
  }
  bool get_staticColor()
  {
    return staticColor;
  }
  void set_fadeColor(bool yes)
  {
    fadeColor = yes;
  }
  bool get_fadeColor()
  {
    return fadeColor;
  }
  void set_randomColor(bool yes)
  {
    randomColor = yes;
  }
  bool get_randomColor()
  {
    return randomColor;
  }

  void set_randomColor_mode(bool yes)
  {
    if (yes == false)
    {
      randomColorStatic = true;
      randomColorTimer = false;
    }
    else
    {
      randomColorTimer = true;
      randomColorStatic = false;
    }
  }

  //solid color vars
  void set_SC_RED(int red)
  {
    SC_RED = red;
  }
  void set_SC_GREEN(int green)
  {
    SC_GREEN = green;
  }
  void set_SC_BLUE(int blue)
  {
    SC_BLUE = blue;
  }
  int get_SC_RED()
  {
    return SC_RED;
  }
  int get_SC_GREEN()
  {
    return SC_GREEN;
  }
  int get_SC_BLUE()
  {
    return SC_BLUE;
  }

  void beginRainbow()
  {
    Pixel_0.r = 255;
    Pixel_0.g = 0;
    Pixel_0.b = 0;
  }
};

colors next_color(colors Farbe)
{
  for (uint8_t Durchgaenge = 0; Durchgaenge < 5; Durchgaenge++)
  {
    if (Farbe.r > 0 && Farbe.b == 0)
    { // Zustand 0
      Farbe.r--;
      Farbe.g++;
    }
    if (Farbe.g > 0 && Farbe.r == 0)
    { // Zustand 1
      Farbe.g--;
      Farbe.b++;
    }
    if (Farbe.b > 0 && Farbe.g == 0)
    { // Zustand 2
      Farbe.b--;
      Farbe.r++;
    }
  }
  return (Farbe);
}

Zeit zeit = Zeit();
ColorScheme colorScheme = ColorScheme();
AsyncWebServer server(80); // 80 = http traffic // SKETCH BEGIN, für den Webserver
String input;
String inputName;

void setup()
{
  strip.begin();
  strip.setBrightness(100);
  strip.clear();
  strip.show();

  Serial.begin(9600); //115200
  Serial.setDebugOutput(true);
  WiFi.begin(ssid, password); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
  pinMode(DATA_PIN, OUTPUT);  // Led als Ausgang definiereyn

  pinMode(DCF_Pin, INPUT);
  Signal = digitalRead(DCF_Pin); // globaler Merker für den Signalzustand

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) { // hört auf /data und macht dann das
    input = request->getParam(0)->value();
    inputName = request->getParam(0)->name();
    Serial.println(inputName + ": " + input);

    if (inputName == "sc_redval") //sortiert nach Variablen und macht mit denen dann was
    {
      colorScheme.set_SC_RED(input.toInt());
    }
    else if (inputName == "sc_greenval")
    {
      colorScheme.set_SC_GREEN(input.toInt());
    }
    else if (inputName == "sc_blueval")
    {
      colorScheme.set_SC_BLUE(input.toInt());
    }
    else if (inputName == "staticColor")
    {
      colorScheme.set_fadeColor(false);
      colorScheme.set_randomColor(false);
      colorScheme.set_staticColor(true);
    }
    else if (inputName == "fadeColor")
    {
      colorScheme.set_randomColor(false);
      colorScheme.set_staticColor(false);
      colorScheme.set_fadeColor(true);
    }
    else if (inputName == "randomColor")
    {
      colorScheme.set_fadeColor(false);
      colorScheme.set_staticColor(false);
      colorScheme.set_randomColor(true);
    }
    else if (inputName == "staticColor_mode")
    {
      if (input.toInt() == 0)
      {
        colorScheme.set_randomColor_mode(false);
      }
      else if (input.toInt() == 1)
      {
        colorScheme.set_randomColor_mode(true);
      }
    }

    colorScheme.update();
    Serial.println("-------------------------");
  });
  server.begin(); // Webserver starten
}

void loop()
{
  Serial.println("kkfkfkfkfkf");
  if (digitalRead(DCF_Pin) != Signal)
  {                   // wenn sich das Signal geändert hat:
    Signal = !Signal; // Merker für Signalzustand invertieren
    if (!Signal)
      fallend = millis();
    else
    { // steigende Flanke (Signal ging von LOW auf HIGH)
      unsigned long diff = fallend - steigend;
      Kodierung[sekunde] = (diff < 150) ? LOW : HIGH;
      steigend = millis();
      strip.setPixelColor(0, 255, 255, 255);

      switch (Zustand)
      {
      case wait_for_DCF:
        Zustand = synchronisiere;
        strip.setPixelColor(1, 255, 255, 255);
        break;
      case synchronisiere:
        if (steigend - fallend > 1300)
        { // ein Signal ist ausgefallen => die Neue Minute beginnt.
          Zustand = ok;
          sekunde = 0;
          strip.setPixelColor(3, 255, 255, 255);
          break;
        }
      case ok:
        if (steigend - fallend > 1300)
        { // ein Signal ist ausgefallen => die Neue Minute beginnt.
          sekunde = 0;
          String Wetter = String(Kodierung[2]) + String(Kodierung[3]) + String(Kodierung[4]) + String(Kodierung[5]) + String(Kodierung[6]) + String(Kodierung[7]) + String(Kodierung[8]) + String(Kodierung[9]) + String(Kodierung[10]) + String(Kodierung[11]) + String(Kodierung[12]) + String(Kodierung[13]) + String(Kodierung[14]) + String(Kodierung[15]);
          int Minute = Kodierung[22] + 2 * Kodierung[23] + 4 * Kodierung[24] + 8 * Kodierung[25] + 10 * Kodierung[26] + 20 * Kodierung[27] + 40 * Kodierung[28];
          int Stunde = Kodierung[30] + 2 * Kodierung[31] + 4 * Kodierung[32] + 8 * Kodierung[33] + 10 * Kodierung[34] + 20 * Kodierung[35];
          int Tag = Kodierung[37] + 2 * Kodierung[38] + 4 * Kodierung[39] + 8 * Kodierung[40] + 10 * Kodierung[41] + 20 * Kodierung[42];
          int Monat = Kodierung[46] + 2 * Kodierung[47] + 4 * Kodierung[48] + 8 * Kodierung[49] + 10 * Kodierung[50];
          int Jahr = Kodierung[51] + 2 * Kodierung[52] + 4 * Kodierung[53] + 8 * Kodierung[54] + 10 * Kodierung[55] + 20 * Kodierung[56] + 40 * Kodierung[57] + 80 * Kodierung[58];

          zeit.set_weather(Wetter);
          zeit.set_minutes(Minute);
          zeit.set_hours(Stunde);
          zeit.set_dayMonth(Tag);
          zeit.set_month(Monat);
          zeit.set_calendarYear(Jahr);
        }
        break;
      }
      sekunde++;
    }
  }
  /*if (millis() >= timestamp + 5)
    {
      colors Pixelfarben = Pixel_0;
      for (int LED = 0; LED < led_count; LED++)
      {
        strip.setPixelColor(LED, Pixelfarben.r, Pixelfarben.g, Pixelfarben.b);
        Pixelfarben = next_color(Pixelfarben);
      }
      Pixel_0 = next_color(Pixel_0);
      strip.show();
    }
    Serial.println("fade");*/
  //timo kaka
  if (colorScheme.get_staticColor())
  {
    for (int i = 0; i < led_count; i++)
    {
      strip.setPixelColor(i, colorScheme.get_SC_RED(), colorScheme.get_SC_GREEN(), colorScheme.get_SC_BLUE());
    }
    //Serial.println("static");
  }
  if (colorScheme.get_fadeColor()) //breathe mit sc col
  {
    for (int i = 0; i < led_count; i++)
      strip.setPixelColor(i, colorScheme.get_SC_RED(), colorScheme.get_SC_GREEN(), colorScheme.get_SC_BLUE());
    if (millis() >= timestamp + 5)
    {
      if (fade_in)
      {
        strip.setBrightness(breathe_index);
        for (int b = 0; b < led_count; b++)
          strip.setPixelColor(b, colorScheme.get_SC_RED(), colorScheme.get_SC_GREEN(), colorScheme.get_SC_BLUE());
        breathe_index++;
        if (breathe_index >= 255)
          fade_in = false;
      }
      else
      {
        strip.setBrightness(breathe_index);
        for (int b = 0; b < led_count; b++)
          strip.setPixelColor(b, colorScheme.get_SC_RED(), colorScheme.get_SC_GREEN(), colorScheme.get_SC_BLUE());
        breathe_index--;
        if (breathe_index <= 0)
          fade_in = true;
      }
      timestamp = millis();
      //Serial.println("fade");
    }
  }
  if (colorScheme.get_randomColor())
  {
    for (int i = 0; i < led_count; i++)
    {
      strip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
    }

    //Serial.println("random");
  }

  for (int i = 0; i <= led_count - 1; i++)
  {
    if (zeit.update()[i] == '0')
    {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }

  strip.show();
}