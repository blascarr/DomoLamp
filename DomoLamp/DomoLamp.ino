#include "config.h"
#include "Debug_Controller.h"

#include <Ticker.h>
#include <Arduino_JSON.h>

#include "DomoLamp_Controller.h"
DomoLamp strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "Server_Controller.h"
#include "WifiManager_Controller.h"
#include "Lamp_Controller.h"

#include "OTA_Controller.h"
#include "Wifi_Controller.h"

#include "WifiEvents_Controller.h"

void setup() {
  Serial.begin(115200);   
  DUMPPRINTLN();
  pinMode( LED_PIN, OUTPUT);
  pinMode( POWERCONTROL_PIN, OUTPUT);
  strip.reset();  //SET GND to HIGH in order to avoid current overflow
  
  onWifiEvents();
  #if OTA
    OTA_init();
  #endif
  strip.init();
  
  bool isConnected = connectToWifi();
  if( isConnected ){
    initWebServer();
  }
}

void loop() {
  #if OTA
    ArduinoOTA.handle();
  #endif
}
