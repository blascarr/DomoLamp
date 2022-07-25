#if defined(ESP32)
  #include <WiFi.h>
  #include <mDNS.h>
#endif

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;

#include <WiFiUdp.h>

#include <ESPAsync_WiFiManager.h> 
DNSServer dns;

Ticker wifiReconnectTimer;
ESPAsync_WiFiManager wifiManager(&server,&dns);
void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  
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
}
