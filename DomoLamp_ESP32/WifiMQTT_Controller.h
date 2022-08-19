#if defined(ESP8266)

  void onWifiConnect(const WiFiEventStationModeGotIP& event) {
    Serial.println("Connected to Wi-Fi From Event.");
    mqtt_reset_trycounter = 0;
    connectToMqtt();
  }
  
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
    Serial.println("Disconnected from Wi-Fi From Event.");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    if( strip.currentStatus.effect != NOWIFI ){
      wifiReconnectTimer.once(3, connectToWifi);
    }
  }
#endif

#if defined(ESP32)
  void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Connected to Wi-Fi From Event.");
    connectToMqtt();
  }
  
  void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from Wi-Fi From Event.");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    if( strip.currentStatus.effect != NOWIFI ){
      wifiReconnectTimer.once(2, connectToWifi);
    }
  }
#endif

void onWifiEvents() {
  #if defined(ESP8266)
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  #endif
  #if defined(ESP32)
    //WiFi.onEvent(onWifiConnect, SYSTEM_EVENT_STA_CONNECTED);
    //WiFi.onEvent(onWifiDisconnect, SYSTEM_EVENT_STA_DISCONNECTED);
  #endif
}
