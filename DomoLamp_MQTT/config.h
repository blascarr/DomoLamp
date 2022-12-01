// ---------------------------------------------------//
// ------------------ WiFi and MQTT ------------------//
// ---------------------------------------------------//
/* --- Set Up Wifi Parameters and MQTT Credentials ---*/
// ------------------ WIFI CONFIG --------------------//

#define WIFIMANAGER   true

#define WIFI_SSID   "SSID"
#define WIFI_PASS   "********"
#define WIFI_HOST   "DOMO_LAMP"
#define LOCAL_IP IPAddress(192, 168, 1, 180)

#define OTA           false
#define OTA_HOST   "DOMO_LAMP"

// ------------------ MQTT CONFIG --------------------//
#define MQTT_HOST_LEN           64
#define MQTT_PORT_LEN           6
#define MQTT_USER_LEN           32
#define MQTT_PASS_LEN           32
#define MQTT_TOPIC_LEN          16
#define MQTT_ACKTOPIC_LEN       16
#define MQTT_QOS                1

char MQTT_HOST [MQTT_HOST_LEN]    = "broker.emqx.io";   //  https://www.emqx.com/en/blog/popular-online-public-mqtt-brokers
char MQTT_PORT   [MQTT_PORT_LEN]  = "1883";
char MQTT_TOPIC   [MQTT_TOPIC_LEN]   = "domo/";
char MQTT_ACKTOPIC   [MQTT_ACKTOPIC_LEN]   = "ack/";
#define MQTT_TOPIC_ID_LEN         16
char DOMOLAMP_ID  [MQTT_TOPIC_ID_LEN]   = "lamp/1";

#define MQTT_CREDENTIALS true
char MQTT_USER  [MQTT_USER_LEN]   = "admin";
char MQTT_PASS  [MQTT_PASS_LEN]   = "*******";

// ---------- NeoPixel CONFIG ---------- //
#define LED_PIN   2
#define LED_COUNT 16
#define POWERCONTROL_PIN   4

// ------------ WIFI CONFIG ------------ //
#define GATEWAY IPAddress(192, 168, 1, 1)
#define SUBNET IPAddress(255, 255, 0, 0)
#define PRIMARYDNS IPAddress(9, 9, 9, 9)
#define SECONDARYDNS IPAddress(208, 67, 222, 222)
#define WIFI_RECONNECT_TIMER_S   20

// ------------ MQTT CONFIG ------------ //
#define MQTT_RESET_MAXTRIES  50
int mqtt_reset_trycounter = 0;

// ----------- SERVER CONFIG ----------- //
#define SERVER_ENDPOINT "/domo"
#define SERVER_EVENTS_ENDPOINT "/domo_events"
#define DATA_REQUEST_INPUT "LampData"
#define SERVER_PORT  80

// ---------- TEST CONFIG ---------- //
#define NOTIFY true
#define NOTIFY_LEDS 2

// ----------- SLEEP CONFIG ----------- //
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define SLEEP_TIME_LEN    10
char SLEEP_TIME  [SLEEP_TIME_LEN] = "3000";

// ---------- STREAM CONFIG ----------- //
#define STREAM_CHARLENGTH 4
#define DEFAULT_BRIGHTNESS 50

// ---------- SERIAL CONFIG ----------- //
#define SERIAL_DEBUG true
#define SERIAL_CONTROL true
long serial_latency = 200;
long serial_millis;

#if SERIAL_DEBUG
    #define SERIALDEBUG Serial
#endif

long time_stamp;
long time_interval = 10;
