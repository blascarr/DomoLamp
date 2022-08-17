#if defined(ESP32)
  #include <WiFi.h>
  #include <mDNS.h>
#endif

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

#if defined(ESP8266)
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
#endif

#include <WiFiUdp.h>

#if WIFIMANAGER 
  #include "ESPAsync_DomoManager/src/ESPAsync_DomoManager.h" 

  ESPAsync_WMParameter  custom_mqtt_server("server", "mqtt server", MQTT_HOST, 40);
  ESPAsync_WMParameter  custom_mqtt_port("port", "mqtt port", MQTT_PORT, 6);
  ESPAsync_WMParameter  custom_mqtt_user("user", "mqtt user", MQTT_USER, 20);
  ESPAsync_WMParameter  custom_mqtt_pass("pass", "mqtt pass", MQTT_PASS, 20);
  ESPAsync_WMParameter  custom_mqtt_topic("topic", "mqtt topic", MQTT_TOPIC, 20);
  ESPAsync_WMParameter  custom_mqtt_acktopic("acktopic", "mqtt acktopic", MQTT_ACKTOPIC, 20);
  ESPAsync_WMParameter  custom_sleep("SleepMode", "Sleep Mode", SLEEP_TIME, 20);
  ESPAsync_WiFiManager wifiManager(&server,&dns);
#endif

Ticker wifiReconnectTimer;

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  #if WIFIMANAGER 
    wifiManager.addParameter(&custom_mqtt_server);
    wifiManager.addParameter(&custom_mqtt_port);
    wifiManager.addParameter(&custom_mqtt_user);
    wifiManager.addParameter(&custom_mqtt_pass);
    wifiManager.addParameter(&custom_mqtt_topic);
    wifiManager.addParameter(&custom_mqtt_acktopic);
    wifiManager.addParameter(&custom_sleep);
    
    bool wifiManagerConnected = wifiManager.autoConnect(WIFI_HOST);
    
    if( wifiManagerConnected ){
        Serial.println("Async WifiManager On");
        Serial.println("connected... :)");
        // Configures static IP address
        if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, PRIMARYDNS, SECONDARYDNS)) {
          Serial.println("STA Failed to configure");
        }
    }
    else {
        Serial.println("Configportal running");
    }
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }
  #else
    WiFi.begin( WIFI_SSID, WIFI_PASS );
    Serial.println("Connecting to Wifi...");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
    }
    
  #endif
  

  Serial.println(WiFi.localIP());
}
