#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <EEPROM.h>
#include <DNSServer.h>

#include <Settings.h>
#include <Read_Write.h>
#include <Effects.h>
#include <Zeit.h>
#include <config.h>
#include <game.h>

#include <index.h>

Settings settings = Settings();
Read_write storage = Read_write();
Zeit zeit = Zeit();
Effects effects = Effects();
Snake snake;

//uhrzeit
WiFiUDP ntpUDP;
//DCF77 DCF = DCF77(DCF_Pin, digitalPinToInterrupt(DCF_Pin));
NTPClient timeClient(ntpUDP, "pool.ntp.org", utc);

//irwas für dcf von ewald
#define ok 2
#define wait_for_DCF 0
#define synchronisiere 1
int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];

//rgb leds ansteuern
const int led_count = 110;
Adafruit_NeoPixel strip(led_count, LED_PIN, NEO_GRB + NEO_KHZ800); // leds init

//webserver
DNSServer dnsServer;
AsyncWebServer server(80); // 80 = http traffic // SKETCH BEGIN, für den Webserver
String inputVar;
String inputName;

void Clear()
{
  for (int i = 0; i < 110; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
}

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
  CaptiveRequestHandler()
  {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/html", SETTINGS_page);
    });
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) { // hört auf /data und macht dann das
      inputVar = request->getParam(0)->value();
      inputName = request->getParam(0)->name();
      Serial.println(inputName + ": " + inputVar);

      if (inputName == "colorMode") //sortiert nach Variablen und macht mit denen dann was
      {
        settings.set_colorMode(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "sc_redval")
      {
        settings.set_SC_RED(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "sc_greenval")
      {
        settings.set_SC_GREEN(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "sc_blueval")
      {
        settings.set_SC_BLUE(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "breathe_redval")
      {
        settings.set_breathe_RED(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "breathe_greenval")
      {
        settings.set_breathe_GREEN(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "breathe_blueval")
      {
        settings.set_breathe_BLUE(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "breathe_delay")
      {
        settings.set_breathe_delay(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "rainbowcycle_verzoegerung")
      {
        settings.set_rainbowcycle_verzoegerung(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "rainbowcycle_farbsprung")
      {
        settings.set_rainbowcycle_farbsprung(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "explosion_redval")
      {
        settings.set_explosion_red(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "explosion_greenval")
      {
        settings.set_explosion_green(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "explosion_blueval")
      {
        settings.set_explosion_blue(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "explosion_delay")
      {
        settings.set_explosion_delay(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "spiral_redval")
      {
        settings.set_spiral_red(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_greenval")
      {
        settings.set_spiral_green(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_blueval")
      {
        settings.set_spiral_blue(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_redval2")
      {
        settings.set_spiral_red2(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_greenval2")
      {
        settings.set_spiral_green2(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_blueval2")
      {
        settings.set_spiral_blue2(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "spiral_delay")
      {
        settings.set_spiral_delay(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else if (inputName == "wlan_ssid")
      {
        settings.set_wlan_ssid(inputVar);
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "wlan_pw")
      {
        settings.set_wlan_pw(inputVar);
        String var;
        for (uint8_t i = 0; i < inputVar.length(); i++)
        {
          var += "\x95";
        }
        request->send(200, "text/plain", inputName + " set to: " + var);
      }
      else if (inputName == "save_wlan")
      {
        storage.saveWlan();
        Serial.println("wlan saved or something");
        while (true)
        {
        }
      }

      else if (inputName == "clockType")
      {
        settings.set_clockType(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "timeType")
      {
        settings.set_timeType(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "DcfWlanMode")
      {
        settings.set_DcfWlanMode(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "brightness")
      {
        settings.set_brightness(inputVar.toInt());
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }
      else if (inputName == "saveALL")
      {
        storage.saveAllSettings();
        request->send(200, "text/plain", "All Settings are saved");
      }
      else if (inputName == "loadALL")
      {
        storage.readAllSettings();
        request->send(200, "text/plain", "All Settings are loaded");
      }

      else if (inputName == "getALL")
      {
        request->send(200, "text/plain", settings.get_all());
      }
      else if (inputName == "crash")
      {
        //request->redirect("https://youtube.com/watch?dQw4w9WgXcQ");
        while (true)
        {
        }
      }

      else if (inputName == "snake_dir")
      {
        settings.set_snake_dir(inputVar.toInt()); //0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
      }

      else
      {
        request->send(404, "text/plain", "404 NOT FOUND: " + String(inputName));
      }
      settings.update();
      Serial.println("-------------------------");
    });
  }
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request)
  {
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", WLAN_page);
  }
};

void setup()
{
  int i = 0;                //boot animation
  pinMode(LED_PIN, OUTPUT); // Led als Ausgang definiereyn
  pinMode(DCF_Pin, INPUT);

  //Serial.begin(9600); //115200 : 9600
  Serial.begin(115200); //115200 : 9600
  delay(100);
  Serial.setDebugOutput(true);

  //Signal = digitalRead(DCF_Pin); // globaler Merker für den Signalzustand

  EEPROM.begin(1024);
  storage.readAllSettings();

  timeClient.begin();

  //Led's Setup Stuff
  strip.begin();
  strip.setBrightness(storage.get_brightness() + 10);
  strip.clear();
  strip.setPixelColor(i, 255, 0, 0);
  i++;
  strip.show();

  //Wifi Setup Stuff
  Serial.print("Hostname: ");
  Serial.println(hostString);
  WiFi.hostname(hostString);
  WiFi.mode(WIFI_STA);
  WiFi.begin(storage.get_wlan_ssid(), storage.get_wlan_pw()); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
  //WiFi.begin(ssid, password); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
  while (WiFi.status() != WL_CONNECTED && settings.get_DcfWlanMode() == 1)
  {
    delay(250);
    Serial.print(".");
    strip.setPixelColor(i, 0, 255, 0);
    i++;
    strip.show();
    if (i >= 100)
    {
      settings.set_DcfWlanMode(0);
      Serial.println("Couldn't connect to any wireless network, switching to DCF");
      WiFi.mode(WIFI_AP);
      WiFi.softAP(hostString);
      dnsServer.start(53, "*", WiFi.softAPIP());
      break;
    }
  }
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //mDNS stuff (hell)
  if (!MDNS.begin(hostString))
  {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  MDNS.addService("esp", "tcp", 8080); // Announce esp tcp service on port 8080

  Serial.println("Sending mDNS query");
  int n = MDNS.queryService("esp", "tcp"); // Send out query for esp tcp services
  Serial.println("mDNS query done");
  if (n == 0)
  {
    Serial.println("no services found");
  }
  else
  {
    Serial.print(n);
    Serial.println(" service(s) found");
    for (int i = 0; i < n; ++i)
    {
      // Print details for each service found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(MDNS.hostname(i));
      Serial.print(" (");
      Serial.print(MDNS.IP(i));
      Serial.print(":");
      Serial.print(MDNS.port(i));
      Serial.println(")");
    }
  }

  strip.setPixelColor(i, 0, 0, 255);
  i++;
  strip.show();
  server.begin(); // Webserver starten
  delay(100);
  Serial.println(String(settings.get_DcfWlanMode()));
  strip.setBrightness(settings.get_brightness());
}

void loop()
{
  //Serial.println("kkfkfkfkfkf"); //ohne dem funkt das programm nicht idk why
  MDNS.update();

  //aktuelle zeit mit dcf77/wlan auslesen und verarbeiten
  if (settings.get_DcfWlanMode() == 0)
  {
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
  }
  else if (settings.get_DcfWlanMode() != 0)
  {
    timeClient.update();

    zeit.set_seconds(timeClient.getSeconds());
    zeit.set_minutes(timeClient.getMinutes());
    zeit.set_hours(timeClient.getHours());
    zeit.set_dayMonth(timeClient.getDay());
  }

  //lichteffekte
  switch (settings.get_colorMode())
  {
  case 0:
    //Clear();
    effects.staticColor();
    break;

  case 1:
    //Clear();
    effects.breathe();
    break;

  case 2:
    //Clear();
    effects.colorCycle();
    break;

  case 3:
    //Clear();
    effects.saison("Halloween");
    break;

  case 4:
    //Clear();
    effects.rainbowCycle();
    break;

  case 5:
    //Clear();
    effects.explosion();
    break;

  case 6:
    //Clear();
    effects.spiral();
    break;

  case 100:
    snake = Snake();
    snake.init();
    settings.set_colorMode(101);
    break;

  case 101:
    snake.loop();
    break;

  case 420:
    break;
  }

  //blendet alles aus was nicht gebraucht wird um die Uhrzeit anzuzeigen
  for (int i = 0; i <= led_count - 1; i++)
  {
    if (zeit.update()[i] == '0')
    {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }

  //Serial.println(String(zeit.get_hours()) + ":" + String(zeit.get_minutes()) + ":" + String(zeit.get_seconds()));
  //zeigt alles an
  strip.show();
}
