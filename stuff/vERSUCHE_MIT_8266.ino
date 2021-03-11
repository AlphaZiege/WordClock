#include <LiquidCrystal_I2C.h>
#define DCF_Pin 14
// Es folgen drei Zustände für die Variable Zustand:
# define wait_for_DCF 0
# define synchronisiere 1
# define ok 2

LiquidCrystal_I2C lcd(0x27, 20, 4);

int sekunde = 0;
bool Signal;
unsigned long steigend = 0, fallend = 0;
uint8_t Zustand = wait_for_DCF;
bool Kodierung[62];

void soundPlay() {
  Serial.write(0x7e); Serial.write(0xff); Serial.write(0x06); Serial.write(0x0d); Serial.write(0x00); Serial.write(0x00); Serial.write(0x00); Serial.write(0xef);
}

void soundStop() {
  Serial.write(0x7e); Serial.write(0xff); Serial.write(0x06); Serial.write(0x0e); Serial.write(0x00); Serial.write(0x00); Serial.write(0x00); Serial.write(0xef);
}

void soundSelect(uint8_t nr) {
  // Auf der SD-Karte im Verzeichnis "01" stehen abspielbare Dateien - Beispiel: "000.mp3" (nr=0) oder "017.mp3" (nr=17)
  Serial.write(0x7e); Serial.write(0xff); Serial.write(0x06); Serial.write(0x0f); Serial.write(0x00); Serial.write(0x01); Serial.write(nr); Serial.write(0xef);
}

void Spiele_Lied(uint8_t Songnumber) {
  soundSelect(Songnumber);
  delay(10);
  soundPlay();
}

void schreibe(int column, int row, String text) {
  lcd.setCursor(column, row);
  lcd.print(text);
}

void setup() {
  Serial.begin(9600, SERIAL_8N1); // Serielle Kommunikation mit dem MP3-Player einstellen
  lcd.init();
  lcd.clear();
  lcd.backlight();
  schreibe(0, 0, "wait");
  pinMode(DCF_Pin, INPUT);
  Signal = digitalRead(DCF_Pin);            // globaler Merker für den Signalzustand
}

void loop() {
  if (digitalRead(DCF_Pin) != Signal) {     // wenn sich das Signal geändert hat:
    Signal = !Signal;                       // Merker für Signalzustand invertieren
    if (!Signal) fallend = millis();
    else {                                  // steigende Flanke (Signal ging von LOW auf HIGH)
      unsigned long diff = fallend - steigend;
      Kodierung[sekunde] = (diff<150) ? LOW : HIGH;
      steigend = millis();
      schreibe(13, 0, String(diff) + "=>" + String(Kodierung[sekunde]) + "  ");

      switch (Zustand) {
        case wait_for_DCF:
          Zustand = synchronisiere;
          schreibe(0, 0, "sync");
          break;
        case synchronisiere:
          if (steigend - fallend > 1300) { // ein Signal ist ausgefallen => die Neue Minute beginnt.
            Zustand = ok;
            sekunde = 0;
            schreibe(0, 0, "run ");
            break;
          }
        case ok:
          if (steigend - fallend > 1300) { // ein Signal ist ausgefallen => die Neue Minute beginnt.
            sekunde = 0;
            int Minute=Kodierung[22]+2*Kodierung[23]+4*Kodierung[24]+8*Kodierung[25]+10*Kodierung[26]+20*Kodierung[27]+40*Kodierung[28];
            int Stunde=Kodierung[30]+2*Kodierung[31]+4*Kodierung[32]+8*Kodierung[33]+10*Kodierung[34]+20*Kodierung[35];
            int Tag=Kodierung[37]+2*Kodierung[38]+4*Kodierung[39]+8*Kodierung[40]+10*Kodierung[41]+20*Kodierung[42];
            int Monat=Kodierung[46]+2*Kodierung[47]+4*Kodierung[48]+8*Kodierung[49]+10*Kodierung[50];
            int Jahr=Kodierung[51]+2*Kodierung[52]+4*Kodierung[53]+8*Kodierung[54]+10*Kodierung[55]+20*Kodierung[56]+40*Kodierung[57]+80*Kodierung[58];
            schreibe(0,3,String(Tag)+"."+String(Monat)+"."+String(Jahr)+" "+String(Stunde)+"."+String(Minute)+" Uhr");
          }
          break;
      }
      sekunde++;
      Spiele_Lied(150);
      schreibe(5, 0, "sec:" + String(sekunde) + " ");
    }
  }
}
