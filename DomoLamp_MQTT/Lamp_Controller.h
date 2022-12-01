Ticker domolampTicker;


void DomoLamp::resetWifiManager( ){
  #if WIFIMANAGER
    DUMPSLN("Reset Wifi Manager");
    #if NOTIFY
      strip.clean();
      strip.fill( NOTIF_PURPLE , 0, 2*NOTIFY_LEDS );
      strip.show(); 
    #endif
    wifiManager.resetSettings();
  #endif
  Serial.println("Reset Wifi Manager");
};

void striploop(){
  strip.loop();
}
