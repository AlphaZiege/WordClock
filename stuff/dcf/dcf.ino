
#include <Arduino.h>
#define DCF_Pin D5
// Es folgen drei Zustände für die Variable Zustand:
#define wait_for_DCF 0
#define synchronisiere 1
#define ok 2

int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];

void setup()
{
  // Serial.begin(9600, SERIAL_8N1); // Serielle Kommunikation mit dem MP3-Player einstellen
  Serial.begin(115200);
  Serial.println("wait");
  pinMode(DCF_Pin, INPUT);
  Signal = digitalRead(DCF_Pin); // globaler Merker für den Signalzustand
}

void loop()
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
      Serial.println(String(diff) + "=>" + String(Kodierung[sekunde]) + "  ");

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
        }
        break;
      }
      sekunde++;
      Serial.println("sec:" + String(sekunde) + " ");
    }
  }
}
