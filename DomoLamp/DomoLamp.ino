#include "config.h"

#include <Ticker.h>
#include "OTA_Controller.h"
#include "Server_Controller.h"
#include "Wifi_Controller.h" 

#include "DomoLamp_Controller.h"
DomoLamp strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "MQTT_Controller.h"
#include "WifiMQTT_Controller.h" 

void setup() {
  Serial.begin(115200);
  Serial.println();

  onWifiEvents();
  OTA_init();
  MQTT_init();
  connectToWifi();
  initWebServer();
  strip.init();
}

void loop() {
  unsigned long currentMillis = millis();
  ArduinoOTA.handle();
  
  if( millis() - time_stamp > time_interval ){
    time_stamp = millis();
    strip.loop();
  }
}
