#if defined(ESP8266)

  void onWifiConnect(const WiFiEventStationModeGotIP& event) {
    DUMPSLN("Connected to Wi-Fi From Event.");
    if(!domolampTicker.active() ){
      DUMPSLN("Ticker Domolamp Init ");
      #if NOTIFY
          strip.fill( NOTIF_GREEN , NOTIFY_LEDS, NOTIFY_LEDS );
          strip.show(); 
      #endif
      domolampTicker.attach_ms( time_interval, striploop );
    }
  }
  
  void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
    DUMPSLN("Disconnected from Wi-Fi From Event.");
    #if NOTIFY
          strip.fill( NOTIF_RED, NOTIFY_LEDS, NOTIFY_LEDS );
          strip.show(); 
    #endif
    if( strip.currentStatus.effect != NOWIFI ){
      wifiReconnectTimer.once(WIFI_RECONNECT_TIMER_S, connectToWifi);
    }
  }
#endif

#if defined(ESP32)
  void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    DUMPSLN("Connected to Wi-Fi From Event.");
    #if NOTIFY
        strip.fill( NOTIF_GREEN, NOTIFY_LEDS, NOTIFY_LEDS );
        strip.show(); 
    #endif
  }
  
  void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    DUMPSLN("Disconnected from Wi-Fi From Event.");
    #if NOTIFY
          strip.fill( NOTIF_RED, NOTIFY_LEDS, NOTIFY_LEDS );
          strip.show(); 
    #endif
    if( strip.currentStatus.effect != NOWIFI ){
      wifiReconnectTimer.once(WIFI_RECONNECT_TIMER_S, connectToWifi);
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
