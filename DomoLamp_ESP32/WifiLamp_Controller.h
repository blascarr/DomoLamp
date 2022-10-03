
void DomoLamp::resetWifiManager( ){
  #if WIFIMANAGER
    wifiManager.resetSettings();
  #endif
  Serial.println("Reset Wifi Manager");
};

void striploop(){
  strip.loop();
}
