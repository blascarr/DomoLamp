#include "config.h"

#include <Ticker.h>
#include <Arduino_JSON.h>

#include "DomoLamp_Controller.h"
DomoLamp strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#include "OTA_Controller.h"
#include "Server_Controller.h"

#include "Wifi_Controller.h" 
#include "MQTT_Controller.h"
#include "WifiMQTT_Controller.h" 
#include "WifiLamp_Controller.h" 

void setup() {
  Serial.begin(115200);   
  Serial.println();

  onWifiEvents();
  OTA_init();
  MQTT_init();
  strip.init();
  domolampTicker.attach_ms( time_interval, striploop );
  connectToWifi();
  initWebServer();
}

void loop() {
  unsigned long currentMillis = millis();
  ArduinoOTA.handle();
}
