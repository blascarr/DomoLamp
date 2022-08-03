// NeoPixel CONFIG
#define LED_PIN   2
#define LED_COUNT 16

// WIFI CONFIG
#define OTA_HOST   "DOMO LAMP"
#define WIFI_HOST   "DOMO LAMP"
#define LOCAL_IP IPAddress(192, 168, 1, 180)
#define GATEWAY IPAddress(192, 168, 1, 1)
#define SUBNET IPAddress(255, 255, 0, 0)
#define PRIMARYDNS IPAddress(9, 9, 9, 9)
#define SECONDARYDNS IPAddress(208, 67, 222, 222)

// MQTT CONFIG
#define MQTT_HOST_LEN           64
#define MQTT_PORT_LEN           6
#define MQTT_USER_LEN           32
#define MQTT_PASS_LEN           32
#define MQTT_TOPIC_LEN           32

char MQTT_HOST [MQTT_HOST_LEN]    = "MQTT_HOST.com";
char MQTT_PORT   [MQTT_PORT_LEN]  = "1883";
char MQTT_USER  [MQTT_USER_LEN]   = "admin";
char MQTT_PASS  [MQTT_PASS_LEN]   = "*********";
char MQTT_TOPIC   [MQTT_TOPIC_LEN]   = "feel/domolamp";

// SERVER CONFIG
#define SERVER_EVENTS_ENDPOINT "/domo_events"

// STREAM CONFIG
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define SLEEP_TIME_LEN    10
char SLEEP_TIME  [SLEEP_TIME_LEN] = "3000";
#define STREAM_CHARLENGTH 4
#define DEFAULT_BRIGHTNESS 50

long time_stamp;
long time_interval = 10;
