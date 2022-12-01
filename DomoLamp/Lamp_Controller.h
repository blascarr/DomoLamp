Ticker domolampTicker;

void DomoLamp::resetWifiManager( ){
  #if WIFIMANAGER
    DUMPSLN("Reset Wifi Manager");
    #if NOTIFY
      strip.fill( NOTIF_PURPLE , 0, 2*NOTIFY_LEDS );
      strip.show(); 
    #endif
    wifiManager.resetSettings();
  #endif
};

void striploop(){
  strip.loop();
}
