#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>

// Wlan Zugang
const char *ssid = "WLAN";
const char *password = "kevin123";

//Pin belegungen
const int DATA_PIN = D3; //LED-Pin
#define DCF_Pin D2       //DCF-Pin

//led matrix maße
const int len_x = 11;
const int len_y = 10;
const int led_count = len_x * len_y;

//irwas für dcf von ewald
#define ok 2
#define wait_for_DCF 0
#define synchronisiere 1

//ewalds DCF
int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];

//timos breathe
unsigned long timestamp;
bool fade_in = true;
int breathe_index = 0;

//rgb leds ansteuern
Adafruit_NeoPixel strip(led_count, DATA_PIN, NEO_GRB + NEO_KHZ800); // leds init

//prototyping
class ColorScheme;
class Zeit;

AsyncWebServer server(80); // 80 = http traffic // SKETCH BEGIN, für den Webserver
String input;
String inputName;

class ColorScheme
{
private:
  bool staticColor, fadeColor, randomColor;
  bool randomColorStatic, randomColorTimer;
  int SC_RED = 0, SC_GREEN = 0, SC_BLUE = 0;

  int timeType = 0 /*timos kack oder normal*/, clockType = 0; //analog / digital idk

public:
  void update()
  {
    strip.setBrightness(255);
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

  //clock modes
  int get_timeType()
  {
    return timeType;
  }
  int get_clockType()
  {
    return clockType;
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
};

ColorScheme colorScheme = ColorScheme();

class Zeit
{
private:
  String weather, zeitsystem;
  int seconds = 0, minutes = 0, hours = 0, dayMonth = 0, dayWeek = 0, month = 0, calendarYear = 0;
  int betterhours;

  void make_betterhours() //wenn 1:30 dann muss halb *2* und nicht halb 1 stehen
  {
    if (minutes >= 18 && colorScheme.get_timeType() == 0)
    {
      betterhours = hours + 1;
    }
    else if (minutes < 18 && colorScheme.get_timeType() == 0)
    {
      betterhours = hours;
    }

    if (minutes >= 12 && colorScheme.get_timeType() == 1)
    {
      betterhours = hours + 1;
    }
    else if (minutes < 12 && colorScheme.get_timeType() == 1)
    {
      betterhours = hours;
    }

    if (betterhours > 12)
    {
      betterhours -= 12;
    }
  }

public:
  //geheimnisprinzip
  void set_weather(String yes)
  {
    weather = yes;
    //needs decode
  }
  String get_weather()
  {
    return weather;
  }
  void set_zeitsystem(String yes)
  {
    zeitsystem = yes;
  }
  String get_zeitsystem()
  {
    return zeitsystem;
  }
  void set_seconds(int yes)
  {
    seconds = yes;
  }
  int get_seconds()
  {
    return seconds;
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
    String table = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    make_betterhours();
    if (colorScheme.get_clockType() == 0) //buchstaben uhr
    {
      table[0] = '1'; //es ist
      table[1] = '1';
      table[3] = '1';
      table[4] = '1';
      table[5] = '1';

      switch (betterhours)
      {
      case 1:
        table[55] = '1'; //eins
        table[56] = '1';
        table[57] = '1';
        table[58] = '1';
        break;

      case 2:
        table[62] = '1'; //zwei
        table[63] = '1';
        table[64] = '1';
        table[65] = '1';
        break;

      case 3:
        table[66] = '1'; //drei
        table[67] = '1';
        table[68] = '1';
        table[69] = '1';
        break;

      case 4:
        table[73] = '1'; //vier
        table[74] = '1';
        table[75] = '1';
        table[76] = '1';
        break;

      case 5:
        table[51] = 'i'; //fünf
        table[52] = '1';
        table[53] = '1';
        table[54] = '1';
        break;

      case 6:
        table[77] = 'i'; //sechs
        table[78] = '1';
        table[79] = '1';
        table[80] = '1';
        table[81] = '1';
        break;

      case 7:
        table[88] = '1'; //sieben
        table[89] = '1';
        table[90] = '1';
        table[91] = '1';
        table[92] = '1';
        table[93] = '1';
        break;

      case 8:
        table[84] = '1'; //acht
        table[85] = '1';
        table[86] = '1';
        table[87] = '1';
        break;

      case 9:
        table[44] = 'i'; //neun
        table[45] = '1';
        table[46] = '1';
        table[47] = '1';
        break;

      case 10:
        table[99] = 'i'; //zehn
        table[100] = '1';
        table[101] = '1';
        table[102] = '1';
        break;

      case 11:
        table[103] = 'i'; //elf
        table[104] = '1';
        table[105] = '1';
        break;

      case 12:
        table[94] = 'i'; //zwölf
        table[95] = '1';
        table[96] = '1';
        table[97] = '1';
        table[98] = '1';
        break;
      }

      switch (minutes)
      {
      case 0 ... 2:
        if (hours == 1)
        {
          table[58] = '0'; //bei ein's' dass s (wird nur bei "es ist ein uhr" nicht gebraucht)
        }
        table[107] = '1'; //uhr
        table[108] = '1';
        table[109] = '1';
        break;

      case 3 ... 7:
        table[7] = '1'; //fünf nach
        table[8] = '1';
        table[9] = '1';
        table[10] = '1';
        table[18] = '1';
        table[19] = '1';
        table[20] = '1';
        table[21] = '1';
        break;

      case 8 ... 12:
        table[11] = '1'; //zehn nach
        table[12] = '1';
        table[13] = '1';
        table[14] = '1';
        table[18] = '1';
        table[19] = '1';
        table[20] = '1';
        table[21] = '1';
        break;

      case 13 ... 17:
        if (colorScheme.get_timeType() == 0) //normale menschen (anto jan)
        {
          table[7] = '1'; //fünfzehn nach
          table[8] = '1';
          table[9] = '1';
          table[10] = '1';
          table[11] = '1';
          table[12] = '1';
          table[13] = '1';
          table[14] = '1';
          table[18] = '1';
          table[19] = '1';
          table[20] = '1';
          table[21] = '1';
        }
        else if (colorScheme.get_timeType() == 1) //timo mit "viertel eins"
        {
          table[25] = '1'; //viertel
          table[26] = '1';
          table[27] = '1';
          table[28] = '1';
          table[29] = '1';
          table[30] = '1';
          table[31] = '1';
        }
        break;

      case 18 ... 22:
        table[11] = '1'; //zehn vor halb
        table[12] = '1';
        table[13] = '1';
        table[14] = '1';
        table[34] = '1';
        table[35] = '1';
        table[36] = '1';
        table[40] = '1';
        table[41] = '1';
        table[42] = '1';
        table[43] = '1';
        break;

      case 23 ... 27:
        table[7] = '1'; //fünf vor halb
        table[8] = '1';
        table[9] = '1';
        table[10] = '1';
        table[34] = '1';
        table[35] = '1';
        table[36] = '1';
        table[40] = '1';
        table[41] = '1';
        table[42] = '1';
        table[43] = '1';
        break;

      case 28 ... 32:
        table[40] = '1'; //halb
        table[41] = '1';
        table[42] = '1';
        table[43] = '1';
        break;

      case 33 ... 37:
        table[7] = '1'; //fünf nach halb
        table[8] = '1';
        table[9] = '1';
        table[10] = '1';
        table[18] = '1';
        table[19] = '1';
        table[20] = '1';
        table[21] = '1';
        table[40] = '1';
        table[41] = '1';
        table[42] = '1';
        table[43] = '1';
        break;

      case 38 ... 42:
        table[11] = '1'; //zehn nach halb
        table[12] = '1';
        table[13] = '1';
        table[14] = '1';
        table[18] = '1';
        table[19] = '1';
        table[20] = '1';
        table[21] = '1';
        table[40] = '1';
        table[41] = '1';
        table[42] = '1';
        table[43] = '1';
        break;

      case 43 ... 47:
        table[25] = '1'; //viertel vor
        table[26] = '1';
        table[27] = '1';
        table[28] = '1';
        table[29] = '1';
        table[30] = '1';
        table[31] = '1';
        table[34] = '1';
        table[35] = '1';
        table[36] = '1';
        break;

      case 48 ... 52:
        table[11] = '1'; //zehn vor
        table[12] = '1';
        table[13] = '1';
        table[14] = '1';
        table[34] = '1';
        table[35] = '1';
        table[36] = '1';
        break;

      case 53 ... 57:
        table[7] = '1'; //fünf vor
        table[8] = '1';
        table[9] = '1';
        table[10] = '1';
        table[34] = '1';
        table[35] = '1';
        table[36] = '1';
        break;

      case 58 ... 62:
        //gleich wie 0 ... 2
        if (hours == 1)
        {
          table[58] = '0'; //bei ein's' dass s (wird nur bei nicht "es ist ein uhr" gebraucht)
        }
        table[107] = '1';
        table[108] = '1';
        table[109] = '1';
        break;
      }

      if (hours == 0 && minutes == 0 && seconds == 0)
      {
        return "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
      }
      else
        return table;
    }

    else if (colorScheme.get_clockType() == 1) //andere uhr
    {
      //gae
    }
  }
};

Zeit zeit = Zeit();


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
  //Serial.println("kkfkfkfkfkf"); //ohne dem funkt das programm nicht idk why

  //aktuelle zeit mit dcf77 auslesen und verarbeiten
  if (digitalRead(DCF_Pin) != Signal)
  {                   // wenn sich das Signal geändert hat:
    Signal = !Signal; // Merker für Signalzustand invertieren
    if (!Signal)
      fallend = millis();
    else
    { // steigende Flanke (Signal ging von LOW auf HIGH)
      unsigned long diff = fallend - steigend;
      Kodierung[sekunde] = (diff < 150) ? LOW : HIGH;
      for (int i = 0; i < sekunde / 60 * led_count; i++)
      {
      strip.setPixelColor(i, Kodierung[sekunde]*255, 0, Kodierung[sekunde]*255);
      }
      steigend = millis();

      switch (Zustand)
      {
      case wait_for_DCF:
        Zustand = synchronisiere;
        strip.setPixelColor(0, 255, 0, 0);
        break;
      case synchronisiere:
        if (steigend - fallend > 1300)
        { // ein Signal ist ausgefallen => die Neue Minute beginnt.
          Zustand = ok;
          sekunde = 0;
          strip.setPixelColor(1, 0, 255, 0);
          break;
        }
      case ok:
        if (steigend - fallend > 1300)
        { // ein Signal ist ausgefallen => die Neue Minute beginnt.
          sekunde = 0;
          String Wetter = String(Kodierung[2]) + String(Kodierung[3]) + String(Kodierung[4]) + String(Kodierung[5]) + String(Kodierung[6]) + String(Kodierung[7]) + String(Kodierung[8]) + String(Kodierung[9]) + String(Kodierung[10]) + String(Kodierung[11]) + String(Kodierung[12]) + String(Kodierung[13]) + String(Kodierung[14]) + String(Kodierung[15]);
          String Zeitsystem = String(Kodierung[16]) + String(Kodierung[17]) + String(Kodierung[18]) + String(Kodierung[19]) + String(Kodierung[20]) + String(Kodierung[21]);
          int Minute = Kodierung[22] + 2 * Kodierung[23] + 4 * Kodierung[24] + 8 * Kodierung[25] + 10 * Kodierung[26] + 20 * Kodierung[27] + 40 * Kodierung[28];
          int Stunde = Kodierung[30] + 2 * Kodierung[31] + 4 * Kodierung[32] + 8 * Kodierung[33] + 10 * Kodierung[34] + 20 * Kodierung[35];
          int Tag = Kodierung[37] + 2 * Kodierung[38] + 4 * Kodierung[39] + 8 * Kodierung[40] + 10 * Kodierung[41] + 20 * Kodierung[42];
          int WochenTag = Kodierung[43] + 2 * Kodierung[44] + 4 * Kodierung[45];
          int Monat = Kodierung[46] + 2 * Kodierung[47] + 4 * Kodierung[48] + 8 * Kodierung[49] + 10 * Kodierung[50];
          int Jahr = Kodierung[51] + 2 * Kodierung[52] + 4 * Kodierung[53] + 8 * Kodierung[54] + 10 * Kodierung[55] + 20 * Kodierung[56] + 40 * Kodierung[57] + 80 * Kodierung[58];

          zeit.set_weather(Wetter);
          zeit.set_zeitsystem(Zeitsystem);
          zeit.set_minutes(Minute);
          zeit.set_hours(Stunde);
          zeit.set_dayMonth(Tag);
          zeit.set_dayWeek(WochenTag);
          zeit.set_month(Monat);
          zeit.set_calendarYear(Jahr);
        }
        break;
      }
      sekunde++;
      zeit.set_seconds(sekunde);
    }
  }

  //lichteffekte
  if (colorScheme.get_staticColor()) //statische Farbe mit sc col
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
  if (colorScheme.get_randomColor()) //zufällige Farbe die sich viel zu schnell ändern
  {

    //Serial.println("random");
  }

  //blendet alles aus was nicht gebraucht wird um die Uhrzeit anzuzeigen
  for (int i = 0; i <= led_count - 1; i++)
  {
    if (zeit.update()[i] == '0')
    {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }

  Serial.println(String(zeit.get_hours()) + ":" + String(zeit.get_minutes()) + ":" + String(zeit.get_seconds()));
  //zeigt alles an
  strip.show();
}