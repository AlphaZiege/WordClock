#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <config.h>
#include <DCF.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <Effects.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <game.h>
#include <NTPClient.h>
#include <Read_Write.h>
#include <Settings.h>
#include <TimeLib.h>
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
Adafruit_NeoPixel strip(110, LED_PIN, NEO_GRB + NEO_KHZ800);
std::array<bool, 110> led_map;

// webserver
DNSServer dnsServer;
AsyncWebServer server(80); // 80 = http traffic // SKETCH BEGIN, für den Webserver
String inputVar;
String inputName;

void setup()
{
    int i = 0; // boot animation counter

    Serial.begin(115200); // 115200 : 9600
    while (!Serial)
        ;

    EEPROM.begin(1024);        // EEPROM initialisieren
    storage.readAllSettings(); // alle gespeicherten Werte einlesen (aktiver Farbmodus usw.)

    Serial.println("\n\n\nBooting...");
    Serial.print("\nHostname: ");
    Serial.println(settings.get_hostname());

    pinMode(LED_PIN, OUTPUT); // Led als Ausgang definieren
    pinMode(DCF_Pin, INPUT);  // DCF Pin als Eingang

    SPIFFS.begin(); // Filesystem begin

    // TimeClient für Onlinezeit
    timeClient.begin();
    timeClient.setTimeOffset(3600);

    // Led's Setup Stuff
    strip.begin();
    strip.setBrightness(storage.get_brightness() + 10);
    strip.clear();
    strip.setPixelColor(i, 0xFFFFFF);
    i++;
    strip.show();

    // Setup Wifi/Dcf
    if (settings.get_DcfWlanMode() != 0)
    {
        strip.setPixelColor(i, 0x006400); // wlan mode -> green
        i++;
        strip.show();
        Serial.print("Attempting to connect to '" + settings.get_wlan_ssid() + "'");

        WiFi.mode(WIFI_STA);
        WiFi.hostname(settings.get_hostname().c_str());
        WiFi.begin(storage.get_wlan_ssid(), storage.get_wlan_pw()); // Aufbau zum Wlan Netzwerk (mit autoreconnect)
        int waittime = 15 * 4 + i;                                  // timeout for wlan connection in sec
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(250);
            Serial.print(".");
            strip.setPixelColor(i, 0x00FF00); // waiting for wlan -> lime
            i++;
            strip.show();
            if (i >= waittime)
            {
                settings.set_DcfWlanMode(0);
                break;
                Serial.println("Couldn't connect to WiFi, switching to DCF77");
            }
        }
        if (i < waittime)
        {
            Serial.print("Connected to '" + WiFi.SSID() + "', IP address: ");
            Serial.println(WiFi.localIP());
        }
    }
    if (settings.get_DcfWlanMode() == 0)
    {
        strip.setPixelColor(i, 0xFF0000); // DCF mode -> red
        i++;
        strip.show();
        WiFi.mode(WIFI_AP);
        WiFi.softAP(settings.get_hostname());
        dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
        dnsServer.start(53, "*", WiFi.softAPIP());

        Signal = digitalRead(DCF_Pin); // globaler Merker für den Signalzustand für DCF
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html"); });
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) { // hört auf /data und macht dann das
        inputVar = request->getParam(0)->value();
        inputName = request->getParam(0)->name();
        Serial.println("-------------------------");
        Serial.println(inputName + ": " + inputVar);

        if (inputName == "colorMode") // sortiert nach Variablen und macht mit denen dann was
        {
            settings.set_colorMode(inputVar.toInt());
        }
        else if (inputName == "colorNightMode")
        {
            settings.set_colorNightMode(inputVar.toInt());
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

        else if (inputName == "noise_redval")
        {
            settings.set_noise_red(inputVar.toInt());
        }
        else if (inputName == "noise_greenval")
        {
            settings.set_noise_green(inputVar.toInt());
        }
        else if (inputName == "noise_blueval")
        {
            settings.set_noise_blue(inputVar.toInt());
        }
        else if (inputName == "noise_delay")
        {
            settings.set_noise_delay(inputVar.toInt());
        }
        else if (inputName == "noise_range")
        {
            settings.set_noise_range(inputVar.toInt());
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
            request->send(200, "text/plain", "Wlan information saved from RAM, please restart to take effect");
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
            if (inputVar == "pudding")
            {
                settings.set_SC_DELAY(333);
            }
            request->send(404, "text/plain", "pschhh");
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
            ESP.restart();
        }

        else if (inputName == "snake_dir")
        {
            settings.set_snake_dir(inputVar.toInt()); // 0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down
        }
        else if (inputName == "tictactoe_field")
        {
            settings.set_tictactoe_field(inputVar.toInt());
        }

        else if (inputName == "hostname")
        {
            settings.set_hostname(inputVar);
        }

        else if (inputName == "forceTime")
        {
            settings.set_DcfWlanMode(5);
            int min, h;

            if (sscanf(inputVar.c_str(), "%d:%d", &h, &min) >= 2)
            {
                zeit.set_minutes(min);
                zeit.set_hours(h);
            }
        }

        else if (inputName == "forceDate")
        {
            settings.set_DcfWlanMode(5);
            int day, mon, year;

            if (sscanf(inputVar.c_str(), "%d.%d.%d", &day, &mon, &year) >= 3)
            {
                zeit.set_dayMonth(day);
                zeit.set_month(mon);
                zeit.set_calendarYear(year);
            }
        }

        else
        {
            request->send(404, "text/plain", "404 NOT FOUND: " + String(inputName));
        }
        request->send(200, "text/plain", inputName + " set to: " + inputVar);
        settings.update();
    });
    server.on("/wlan", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/wlan.html"); });
    server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/restarting.html"); });
    server.on("/live", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "yes"); });
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/favicon.png", "image/png"); });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/javascript"); });
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
                          if (settings.get_DcfWlanMode() == 0)
                              request->send(SPIFFS, "/wlan.html");
                          else
                              request->send(SPIFFS, "/notfound.html"); });

    // mDNS stuff
    MDNS.begin(settings.get_hostname());
    MDNS.addService("esp", "tcp", 8080); // Announce esp tcp service on port 8080

    Serial.println("Sending mDNS query");
    int n = MDNS.queryService("esp", "tcp"); // Send out query for esp tcp services
    if (n == 0)
    {
        Serial.println("no services found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" service(s) found");
        for (int j = 0; j < n; ++j)
        {
            // Print details for each service found
            Serial.print(j + 1);
            Serial.print(": ");
            Serial.print(MDNS.hostname(j));
            Serial.print(" (");
            Serial.print(MDNS.IP(j));
            Serial.print(":");
            Serial.print(MDNS.port(j));
            Serial.println(")");
            strip.setPixelColor(i, 0xFFFF00);
            i++;
        }
        strip.show();
    }

    server.begin(); // Webserver starten
    delay(100);

    strip.setPixelColor(i, 0xFFFFFF);
    strip.show();
    delay(100);
    strip.setBrightness(settings.get_brightness());

    Serial.println("Setup finished");
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
                if (Kodierung[sekunde])
                    strip.setPixelColor(sekunde, 0xFFFFFF);
                else
                    strip.setPixelColor(sekunde, 0xFF00FF);

                switch (Zustand)
                {
                case wait_for_DCF:
                    Zustand = synchronisiere;
                    strip.clear();
                    settings.set_colorMode(420);
                    Serial.println("preparing to sync");
                    break;
                case synchronisiere:
                    if (steigend - fallend > 1300)
                    { // ein Signal ist ausgefallen => die Neue Minute beginnt.
                        Zustand = ok;
                        sekunde = 0;
                        Serial.println("syncing...");
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

                        if (checkValidity(Kodierung))
                        {
                            Serial.println(String(Tag) + "." + String(Monat) + "." + String(Jahr + 2000) + " " + String(Stunde) + "." + String(Minute) + " Uhr");
                            zeit.set_calendarYear(Jahr + 2000);
                            zeit.set_month(Monat);
                            zeit.set_dayMonth(Tag);
                            zeit.set_minutes(Minute);
                            zeit.set_hours(Stunde);

                            settings.set_colorMode(storage.get_colorMode());
                        }
                        else
                        {
                            Serial.println(String(Tag) + "." + String(Monat) + "." + String(Jahr + 2000) + " " + String(Stunde) + "." + String(Minute) + " Uhr, invalid");
                            strip.clear();
                        }
                    }
                    break;
                }
                zeit.set_seconds(sekunde);
                sekunde++;
            }
        }
    }
    else if (settings.get_DcfWlanMode() == 1)
    {
        epochTime = timeClient.getEpochTime();

        zeit.set_calendarYear(year(epochTime));
        zeit.set_month(month(epochTime));
        zeit.set_dayMonth(day(epochTime));
        zeit.set_dayWeek(weekday(epochTime));
        zeit.set_seconds(second(epochTime));
        zeit.set_minutes(minute(epochTime));
        zeit.set_hours(hour(epochTime));

        // if (zeit.summertime_EU(2022, 4, 13, 13, 1))
        if (zeit.summertime_EU(zeit.get_calendarYear(), zeit.get_month(), zeit.get_dayMonth(), zeit.get_hours(), 1))
        {
            timeClient.setTimeOffset(7200);
        }
        else
            timeClient.setTimeOffset(3600);
        while (!timeClient.update())
        {
            timeClient.forceUpdate();
        }
    }

    settings.calcOffHours();

    strip.setBrightness(settings.get_currentBrightness());

    switch (settings.get_CurrentColorMode())
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

    case 8:
        effects.noise();
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
    led_map = zeit.update();
    for (int i = 0; i <= led_count - 1; i++)
    {
        if (led_map[i] == false)
        {
            strip.setPixelColor(i, 0x000000);
        }
    }
    strip.show();
}
