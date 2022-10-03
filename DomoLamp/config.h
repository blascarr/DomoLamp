// ---------------------------------------------------//
// ------------------ WiFi and MQTT ------------------//
// ---------------------------------------------------//
/* --- Set Up Wifi Parameters and MQTT Credentials ---*/
// ------------------ WIFI CONFIG --------------------//

#define WIFIMANAGER   true
#define WIFI_SSID   "ZMS_SSID"
#define WIFI_PASS   "**********"
#define OTA_HOST   "DOMO_LAMP"
#define WIFI_HOST   "DOMO_LAMP"
#define LOCAL_IP IPAddress(192, 168, 1, 180)

// ------------------ MQTT CONFIG --------------------//
#define MQTT_HOST_LEN           64
#define MQTT_PORT_LEN           6
#define MQTT_USER_LEN           32
#define MQTT_PASS_LEN           32
#define MQTT_TOPIC_LEN          16
#define MQTT_ACKTOPIC_LEN       16
#define MQTT_QOS                1

char MQTT_HOST [MQTT_HOST_LEN]    = "mqtt.host.com";
char MQTT_PORT   [MQTT_PORT_LEN]  = "1883";
char MQTT_USER  [MQTT_USER_LEN]   = "admin";
char MQTT_PASS  [MQTT_PASS_LEN]   = "**********";
char MQTT_TOPIC   [MQTT_TOPIC_LEN]   = "domo/";
char MQTT_ACKTOPIC   [MQTT_ACKTOPIC_LEN]   = "ack/";

#define MQTT_TOPIC_ID_LEN         16
char DOMOLAMP_ID  [MQTT_TOPIC_ID_LEN]   = "D0M0L4MP";

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

// ----------- SLEEP CONFIG ----------- //
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define SLEEP_TIME_LEN    10
char SLEEP_TIME  [SLEEP_TIME_LEN] = "3000";

// ---------- STREAM CONFIG ----------- //
#define STREAM_CHARLENGTH 4
#define DEFAULT_BRIGHTNESS 50

long time_stamp;
long time_interval = 10;
