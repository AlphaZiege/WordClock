#include <Arduino.h>
#include <ArduinoJson.h>
#include <config.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <Effects.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FastLED.h>
#include <FS.h>
#include <game.h>
#include <NTPClient.h>
#include <Read_Write.h>
#include <Settings.h>
#include <Zeit.h>

Effects effects = Effects();
Read_write storage = Read_write();
Settings settings = Settings();
Snake snake;
TicTacToe tictactoe;
Zeit zeit = Zeit();
DynamicJsonDocument doc(1024);

// uhrzeit
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
unsigned long epochTime;
struct tm *ptm;

// offhours
uint16_t curr_time;
uint16_t offBegin_time;
uint16_t offEnd_time;

// filesystem
// FS &filesystem =SPIFFS;

// dcf
#define wait_for_DCF 0
#define synchronisiere 1
#define ok 2
int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];

// rgb leds ansteuern
const int led_count = 110;
CRGB leds[led_count];

// webserver
DNSServer dnsServer;
AsyncWebServer server(80); // 80 = http traffic // SKETCH BEGIN, für den Webserver
String inputVar;
String inputName;

WiFiClient client;

void setup()
{
    settings.set_hostname(hostString);
    int i = 0;                // boot animation
    pinMode(LED_PIN, OUTPUT); // Led als Ausgang definieren
    pinMode(DCF_Pin, INPUT);  // DCF Pin als Eingang

    // Serial.begin(9600); //115200 : 9600
    Serial.begin(115200); // 115200 : 9600
    while (!Serial)
        ;
    Serial.setDebugOutput(true);

    Signal = digitalRead(DCF_Pin); // globaler Merker für den Signalzustand für DCF

    SPIFFS.begin();

    EEPROM.begin(1024);        // EEPROM initialisieren
    storage.readAllSettings(); // alle gespeicherten Werte einlesen (aktiver Farbmodus usw.)

    // TimeClient für Onlinezeit
    timeClient.begin();
    timeClient.setTimeOffset(3600);

    // Led's Setup Stuff
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, led_count);
    FastLED.setDither(0);

    FastLED.setBrightness(storage.get_brightness() + 10);
    FastLED.clear(true);
    // strip.setPixelColor(i, 0, 255, 0);
    leds[i] = CRGB::Lime;
    FastLED.show();
    i++;

    // Wifi Setup Stuff
    Serial.print("Hostname: ");
    Serial.println(hostString);
    WiFi.hostname(hostString);
    if (settings.get_DcfWlanMode() != 0)
    {
        leds[i] = CRGB::White;
        WiFi.mode(WIFI_STA);
        WiFi.begin(storage.get_wlan_ssid(), storage.get_wlan_pw()); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
    }
    else
    {
        leds[i] = CRGB::Blue;
    }
    FastLED.show();
    i++;
    // WiFi.begin("ssid", "password"); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");
        leds[i] = CRGB::Aqua;
        i++;
        FastLED.show();
        if (i >= 60 || settings.get_DcfWlanMode() == 0)
        {
            settings.set_DcfWlanMode(0);
            Serial.println("Couldn't connect to any wireless network, switching to DCF");
            WiFi.mode(WIFI_AP);
            WiFi.softAP(hostString);
            dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
            dnsServer.start(53, "*", WiFi.softAPIP());
            break;
        }
    }
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html"); });
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) { // hört auf /data und macht dann das
        inputVar = request->getParam(0)->value();
        inputName = request->getParam(0)->name();
        Serial.println(inputName + ": " + inputVar);

        if (inputName == "colorMode") // sortiert nach Variablen und macht mit denen dann was
        {
            settings.set_colorMode(inputVar.toInt());
        }

        else if (inputName == "sc_redval")
        {
            settings.set_SC_RED(inputVar.toInt());
        }
        else if (inputName == "sc_greenval")
        {
            settings.set_SC_GREEN(inputVar.toInt());
        }
        else if (inputName == "sc_blueval")
        {
            settings.set_SC_BLUE(inputVar.toInt());
        }

        else if (inputName == "breathe_redval")
        {
            settings.set_breathe_RED(inputVar.toInt());
        }
        else if (inputName == "breathe_greenval")
        {
            settings.set_breathe_GREEN(inputVar.toInt());
        }
        else if (inputName == "breathe_blueval")
        {
            settings.set_breathe_BLUE(inputVar.toInt());
        }
        else if (inputName == "breathe_delay")
        {
            settings.set_breathe_delay(inputVar.toInt());
        }

        else if (inputName == "rainbowcycle_verzoegerung")
        {
            settings.set_rainbowcycle_verzoegerung(inputVar.toInt());
        }
        else if (inputName == "rainbowcycle_farbsprung")
        {
            settings.set_rainbowcycle_farbsprung(inputVar.toInt());
        }

        else if (inputName == "explosion_redval")
        {
            settings.set_explosion_red(inputVar.toInt());
        }
        else if (inputName == "explosion_greenval")
        {
            settings.set_explosion_green(inputVar.toInt());
        }
        else if (inputName == "explosion_blueval")
        {
            settings.set_explosion_blue(inputVar.toInt());
        }
        else if (inputName == "explosion_redval2")
        {
            settings.set_explosion_red2(inputVar.toInt());
        }
        else if (inputName == "explosion_greenval2")
        {
            settings.set_explosion_green2(inputVar.toInt());
        }
        else if (inputName == "explosion_blueval2")
        {
            settings.set_explosion_blue2(inputVar.toInt());
        }
        else if (inputName == "explosion_delay")
        {
            settings.set_explosion_delay(inputVar.toInt());
        }

        else if (inputName == "spiral_redval")
        {
            settings.set_spiral_red(inputVar.toInt());
        }
        else if (inputName == "spiral_greenval")
        {
            settings.set_spiral_green(inputVar.toInt());
        }
        else if (inputName == "spiral_blueval")
        {
            settings.set_spiral_blue(inputVar.toInt());
        }
        else if (inputName == "spiral_redval2")
        {
            settings.set_spiral_red2(inputVar.toInt());
        }
        else if (inputName == "spiral_greenval2")
        {
            settings.set_spiral_green2(inputVar.toInt());
        }
        else if (inputName == "spiral_blueval2")
        {
            settings.set_spiral_blue2(inputVar.toInt());
        }
        else if (inputName == "spiral_delay")
        {
            settings.set_spiral_delay(inputVar.toInt());
        }

        else if (inputName == "wlan_ssid")
        {
            settings.set_wlan_ssid(inputVar);
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
        }
        else if (inputName == "timeType")
        {
            settings.set_timeType(inputVar.toInt());
        }
        else if (inputName == "DcfWlanMode")
        {
            settings.set_DcfWlanMode(inputVar.toInt());
        }
        else if (inputName == "brightness")
        {
            settings.set_brightness(inputVar.toInt());
        }
        else if (inputName == "offhour_brightness")
        {
            settings.set_offhours_brightness(inputVar.toInt());
        }
        else if (inputName == "offhour_begin_h")
        {
            settings.set_offhours_begin_h(inputVar.toInt());
        }
        else if (inputName == "offhour_end_h")
        {
            settings.set_offhours_end_h(inputVar.toInt());
        }
        else if (inputName == "offhour_begin_m")
        {
            settings.set_offhours_begin_m(inputVar.toInt());
        }
        else if (inputName == "offhour_end_m")
        {
            settings.set_offhours_end_m(inputVar.toInt());
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
            if (inputVar == "pudding")
            {
                settings.set_SC_DELAY(333);
            }
        }
        else if (inputName == "getJSON")
        {
            settings.generateJson(version);
            String output;
            if (inputVar.toInt() == 1)
            {
                serializeJsonPretty(doc, output);
            }
            else
            {
                serializeJson(doc, output);
            }
            request->send(200, "application/json", output);
        }

        else if (inputName == "crash")
        {
            // request->redirect("https://youtube.com/watch?dQw4w9WgXcQ");
            ESP.reset();
        }

        else if (inputName == "snake_dir")
        {
            settings.set_snake_dir(inputVar.toInt()); // 0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down
        }
        else if (inputName == "tictactoe_field")
        {
            settings.set_tictactoe_field(inputVar.toInt());
        }

        else
        {
            request->send(404, "text/plain", "404 NOT FOUND: " + String(inputName));
        }
        request->send(200, "text/plain", inputName + "set to: " + inputVar);
        settings.update();
        Serial.println("-------------------------");
    });
    server.on("/wlan", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/wlan.html"); });
    server.on("/live", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "yes"); });
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/favicon.png", "image/png"); });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
                          if (settings.get_DcfWlanMode() == 0)
                              request->send(SPIFFS, "/wlan.html");
                          else
                              request->send(SPIFFS, "/notfound.html");
                      });

    Serial.print("Connected to " + WiFi.SSID() + " IP address: ");
    Serial.println(WiFi.localIP());

    // mDNS stuff
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

    leds[i] = CRGB::Blue;
    i++;
    FastLED.show();
    server.begin(); // Webserver starten
    delay(100);
    // Serial.println(String(settings.get_DcfWlanMode()));

    leds[i] = CRGB::White;
    FastLED.show();
    delay(100);
    FastLED.setBrightness(settings.get_brightness());
}

void loop()
{
    MDNS.update();
    dnsServer.processNextRequest();

    // aktuelle zeit mit dcf77/wlan auslesen und verarbeiten
    if (settings.get_DcfWlanMode() == 0)
    {
        // Serial.println(String(digitalRead(DCF_Pin)));
        if (digitalRead(DCF_Pin) != Signal)
        {
            // wenn sich das Signal geändert hat:
            Signal = !Signal; // Merker für Signalzustand invertieren
            if (!Signal)
                fallend = millis();
            else
            { // steigende Flanke (Signal ging von LOW auf HIGH)
                unsigned long diff = fallend - steigend;
                Kodierung[sekunde] = (diff < 150) ? LOW : HIGH;
                steigend = millis();
                // Serial.println(String(diff) + "=>" + String(Kodierung[sekunde]) + "  ");

                switch (Zustand)
                {
                case wait_for_DCF:
                    Zustand = synchronisiere;
                    Serial.println("sync");
                    break;
                case synchronisiere:
                    if (steigend - fallend > 1300)
                    { // ein Signal ist ausgefallen => die Neue Minute beginnt.
                        Zustand = ok;
                        sekunde = 0;
                        Serial.println("run ");
                        break;
                    }
                case ok:
                    if (steigend - fallend > 1300)
                    { // ein Signal ist ausgefallen => die Neue Minute beginnt.
                        sekunde = 0;
                        int Minute = Kodierung[22] + 2 * Kodierung[23] + 4 * Kodierung[24] + 8 * Kodierung[25] + 10 * Kodierung[26] + 20 * Kodierung[27] + 40 * Kodierung[28];
                        int Stunde = Kodierung[30] + 2 * Kodierung[31] + 4 * Kodierung[32] + 8 * Kodierung[33] + 10 * Kodierung[34] + 20 * Kodierung[35];
                        int Tag = Kodierung[37] + 2 * Kodierung[38] + 4 * Kodierung[39] + 8 * Kodierung[40] + 10 * Kodierung[41] + 20 * Kodierung[42];
                        int Monat = Kodierung[46] + 2 * Kodierung[47] + 4 * Kodierung[48] + 8 * Kodierung[49] + 10 * Kodierung[50];
                        int Jahr = Kodierung[51] + 2 * Kodierung[52] + 4 * Kodierung[53] + 8 * Kodierung[54] + 10 * Kodierung[55] + 20 * Kodierung[56] + 40 * Kodierung[57] + 80 * Kodierung[58];
                        Serial.println(String(Tag) + "." + String(Monat) + "." + String(Jahr) + " " + String(Stunde) + "." + String(Minute) + " Uhr");
                        zeit.set_calendarYear(Jahr + 2000);
                        zeit.set_month(Monat);
                        zeit.set_dayMonth(Tag);
                        zeit.set_minutes(Minute);
                        zeit.set_hours(Stunde);
                    }
                    break;
                }
                zeit.set_seconds(sekunde);
                sekunde++;
                // Serial.println("sec:" + String(sekunde) + " ");
            }
        }
    }
    else if (settings.get_DcfWlanMode() != 0)
    {
        epochTime = timeClient.getEpochTime();
        tm *ptm = gmtime((time_t *)&epochTime);

        zeit.set_calendarYear(ptm->tm_year + 1900);
        zeit.set_month(ptm->tm_mon + 1);
        zeit.set_dayMonth(ptm->tm_mday);
        zeit.set_seconds(timeClient.getSeconds());
        zeit.set_minutes(timeClient.getMinutes());
        zeit.set_hours(timeClient.getHours());
        // zeit.set_dayMonth(timeClient.getDay());

        if (zeit.summertime_EU(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, timeClient.getHours(), 1))
        {
            timeClient.setTimeOffset(7200);
        }
        while (!timeClient.update())
        {
            timeClient.forceUpdate();
        }
    }

    // offhours
    curr_time = (zeit.get_hours() * 60) + (zeit.get_minutes());
    offBegin_time = (settings.get_offhours_begin_h() * 60) + (settings.get_offhours_begin_m());
    offEnd_time = (settings.get_offhours_end_h() * 60) + (settings.get_offhours_end_m());

    if (curr_time > offBegin_time && curr_time < offEnd_time)
    {
        FastLED.setBrightness(settings.get_offhours_brightness());
    }
    else if (offBegin_time > offEnd_time && (curr_time > offBegin_time || curr_time < offEnd_time))
    {
        FastLED.setBrightness(settings.get_offhours_brightness());
    }
    else
    {
        FastLED.setBrightness(settings.get_brightness());
    }

    // lichteffekte
    switch (settings.get_colorMode())
    {
    case 0:
        effects.staticColor();
        break;

    case 1:
        effects.breathe();
        break;

    case 2:
        effects.colorCycle();
        break;

    case 3:
        effects.saison("Halloween");
        break;

    case 4:
        effects.rainbowCycle();
        break;

    case 5:
        effects.explosion();
        break;

    case 6:
        effects.spiral();
        break;

    case 7:
        effects.rain();
        break;

    case 100:
        snake = Snake();
        settings.set_colorMode(101);
        break;

    case 101:
        snake.loop();
        break;

    case 102:
        snake.GameoverLoop();
        break;

    case 103:
        tictactoe = TicTacToe();
        settings.set_tictactoe_field(0);
        settings.set_colorMode(104);
        break;

    case 104:
        tictactoe.Loop();
        break;

    case 420:
        break;
    }

    // blendet alles aus was nicht gebraucht wird um die Uhrzeit anzuzeigen
    for (int i = 0; i <= led_count - 1; i++)
    {
        if (zeit.update()[i] == '0')
        {
            leds[i] = CRGB::Black;
        }
    }
    // Serial.println(String(zeit.get_hours()) + ":" + String(zeit.get_minutes()) + ":" + String(zeit.get_seconds()));
    // zeigt alles an
    FastLED.show();
}
