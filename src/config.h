//Name der Uhr
const char *hostString = "WordClock_0";
const String version = "0.2";

//Pin belegungen
#define LED_PIN D6 //LED-Pin
#define DCF_Pin D5 //DCF-Pin

//fastLED cfg
#define FASTLED_ESP8266_RAW_PIN_ORDER LED_PIN
#define FASTLED_INTERRUPT_RETRY_COUNT 1
