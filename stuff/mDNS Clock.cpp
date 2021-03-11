#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>

#define STASSID "Nicht Verbunden"
#define STAPSK  "FgpExnALzFpuFZnc"

const char*                   ssid                    = STASSID;
const char*                   password                = STAPSK;

char*                         pcHostDomain            = 0;        // Negociated host domain

void setup(void) {
  Serial.begin(9600);

  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Init the (currently empty) host domain string with 'esp8266'
  if ((!MDNSResponder::indexDomain(pcHostDomain, 0, "esp8266")) ||
      (!MDNS.begin(pcHostDomain))) {
    Serial.println("Error setting up MDNS responder!");
    while (1) { // STOP
      delay(1000);
    }
  }
  Serial.println("MDNS responder started");
}

void loop(void) {

  // Allow MDNS processing
  MDNS.update();
}