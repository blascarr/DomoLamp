#define OTA_HOST   "DOMO LAMP"
#define WIFI_HOST   "DOMO LAMP"

// WIFI CONFIG
#define LOCAL_IP IPAddress(192, 168, 1, 180)
#define GATEWAY IPAddress(192, 168, 1, 1)
#define SUBNET IPAddress(255, 255, 0, 0)
#define PRIMARYDNS IPAddress(9, 9, 9, 9)
#define SECONDARYDNS IPAddress(208, 67, 222, 222)

// MQTT CONFIG
//#define MQTT_HOST IPAddress(194, 135, 80, 53)
#define MQTT_HOST "MQTT_HOST"
#define MQTT_PORT 1883
#define MQTT_USER "admin"
#define MQTT_PASS "*********"

// MQTT Topics
#define MQTT_TOPIC "feel/domolamp"
#define MQTT_TOPIC_PUSH "feelme/domolamp"

// NeoPixel CONFIG
#define LED_PIN   2
#define LED_COUNT 16

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  3        /* Time ESPo266 will go to sleep (in seconds) */
#define STREAM_CHARLENGTH 4
#define DEFAULT_BRIGHTNESS 50

long time_stamp;
long time_interval = 10;
