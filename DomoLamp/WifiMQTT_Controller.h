#if defined(ESP8266)

  void onWifiConnect(const WiFiEventStationModeGotIP& event) {
    Serial.println("Connected to Wi-Fi.");
    mqtt_reset_trycounter = 0;
    
    if(!domolampTicker.active() ){
      Serial.println("Ticker Domolamp Init ");
      domolampTicker.attach_ms( time_interval, striploop );
    }
    connectToMqtt();
  }
  
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
    Serial.println("Disconnected from Wi-Fi.");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    if( strip.currentStatus.effect != NOWIFI ){
      wifiReconnectTimer.once(WIFI_RECONNECT_TIMER_S, connectToWifi);
    }
  }
#endif

#if defined(ESP32)
  void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Connected to Wi-Fi.");
    connectToMqtt();
  }
  
  void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("Disconnected from Wi-Fi.");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    wifiReconnectTimer.once(WIFI_RECONNECT_TIMER_S, connectToWifi);
  }
#endif

void onWifiEvents() {
  #if defined(ESP8266)
    wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
  #endif
  #if defined(ESP32)
    WiFi.onEvent(onWifiConnect, SYSTEM_EVENT_STA_CONNECTED);
    WiFi.onEvent(onWifiDisconnect, SYSTEM_EVENT_STA_DISCONNECTED);
  #endif
}
