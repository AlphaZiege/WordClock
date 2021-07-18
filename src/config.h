//Name der Uhr
const char *hostString = "WordClock_0";
const String version = "0.1";

//Pin belegungen
#define LED_PIN D6 //LED-Pin
#define DCF_Pin D5 //DCF-Pin

//mysql
IPAddress server_addr(192,168,178,61);
char mysql_user[] = "anto";
char mysql_password[] = "doener";        // MySQL user login password
