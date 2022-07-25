#include <ESP8266WiFi.h>
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
#include <ESP8266mDNS.h>
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
