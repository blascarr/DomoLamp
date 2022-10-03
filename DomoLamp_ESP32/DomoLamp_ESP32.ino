#include "config.h"

#include <Ticker.h>
#include <Arduino_JSON.h>

#include "DomoLamp_Controller.h"
DomoLamp strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Ticker domolampTicker;

#include "OTA_Controller.h"
#include "Server_Controller.h"

#include "Wifi_Controller.h"
#include "MQTT_Controller.h"
#include "WifiLamp_Controller.h"
#include "WifiMQTT_Controller.h"

void setup() {
  Serial.begin(115200);   
  Serial.println();
  pinMode( LED_PIN, OUTPUT);
  pinMode( POWERCONTROL_PIN, OUTPUT);
  strip.reset();  //SET GND to HIGH in order to avoid current overflow
  
  onWifiEvents();
  //OTA_init();
  connectToWifi();
  MQTT_init();
  connectToMqtt();
  initWebServer();
  strip.init();
}

void loop() {
  ArduinoOTA.handle();
}
