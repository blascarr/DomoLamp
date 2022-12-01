#include <AsyncMqttClient.h>
Ticker mqttReconnectTimer;

AsyncMqttClient mqttClient;

void connectToMqtt() {
  DUMPSLN("Connecting to MQTT...");
  mqttClient.connect();
  delay(1000);
  if( !mqttClient.connected()){
    DUMPSLN("Invalid MQTT Credentials\n");
    #if NOTIFY
        strip.clean();
        strip.fill( NOTIF_RED , 0, 3*NOTIFY_LEDS );
        strip.show(); 
    #endif
  }else{
    #if NOTIFY
        strip.clean();
        strip.fill( NOTIF_GREEN , 0, 3*NOTIFY_LEDS );
        strip.show(); 
    #endif
  }
}

void onMqttConnect(bool sessionPresent) {
  DUMPSLN("Connected to MQTT.");
  DUMPLN("Session present: ", sessionPresent);
  
  char topic[strlen(MQTT_TOPIC)+strlen(DOMOLAMP_ID)];
  strcpy(topic, MQTT_TOPIC ); 
  strcat(topic, DOMOLAMP_ID);
  mqttClient.subscribe( topic, MQTT_QOS );
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  mqtt_reset_trycounter++;
  DUMPLN("Disconnected from MQTT. Try : ", mqtt_reset_trycounter);
  if( mqtt_reset_trycounter > MQTT_RESET_MAXTRIES){
    #if WIFIMANAGER
      wifiManager.resetSettings();
      #if NOTIFY
          strip.clean();
          strip.fill( NOTIF_PURPLE , 0, 3*NOTIFY_LEDS );
          strip.show(); 
      #endif
    #endif
    //strip.currentStatus.color = strip.Color( 0 , 0, 0 );
    //strip.light = &DomoLamp::blink;
    ESP.restart();
  }else{
    if (WiFi.isConnected()) {
      mqttReconnectTimer.once(2, connectToMqtt);
    }
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  DUMPS("Subscribe acknowledged.\t ");
  DUMPLN("  packetId: ", packetId);
  DUMPLN("  qos: ",qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  DUMPS("Unsubscribe acknowledged. \t ");
  DUMPLN("  packetId: ", packetId);
}

void onMqttPublish(uint16_t packetId) {
  DUMPS("Publish acknowledged. \t ");
  DUMPLN("  packetId: ", packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  DUMPSLN("Publish received.");
  DUMPLN("  topic: ", topic);
  DUMPLN("  qos: ", properties.qos);
  DUMPLN("  dup: ", properties.dup);
  DUMPLN("  retain: ", properties.retain);
  DUMPLN("  len: ", len);
  DUMPLN("  index: ", index);
  DUMPLN("  total: ", total);
  DUMPLN(" Payload: ", payload );
  char messageArray[len];
  memcpy ( messageArray, payload, len );
  String message(messageArray);
  DUMPVLN( message );
  strip.setStatus( message );
  
  //  Publish Received ACK message
  #if WIFIMANAGER
    strncpy(MQTT_ACKTOPIC, custom_mqtt_acktopic.getValue(), sizeof(MQTT_ACKTOPIC));
  #endif
  
  String ack_message = "Received from : "+ String(DOMOLAMP_ID);
  char ack_buf[ ack_message.length()+1 ];
  ack_message.toCharArray(ack_buf, ack_message.length() +1);
  
  char ack_topic[strlen(MQTT_ACKTOPIC)+strlen(DOMOLAMP_ID)];
  strcpy(ack_topic, MQTT_ACKTOPIC ); 
  strcat(ack_topic, DOMOLAMP_ID);
  
  mqttClient.publish( ack_topic, MQTT_QOS, false, ack_buf, ack_message.length()+1 );
}

void MQTT_init(){
  mqttClient.setClientId(DOMOLAMP_ID);
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.onMessage(onMqttMessage);

  #if WIFIMANAGER
    strncpy(MQTT_HOST, custom_mqtt_server.getValue(), sizeof(MQTT_HOST));
    strncpy(MQTT_PORT, custom_mqtt_port.getValue(), sizeof(MQTT_PORT));

    #if MQTT_CREDENTIALS
      strncpy(MQTT_USER, custom_mqtt_user.getValue(), sizeof(MQTT_USER));
      strncpy(MQTT_PASS, custom_mqtt_pass.getValue(), sizeof(MQTT_PASS));
    #endif
  #endif
  mqttClient.setServer(MQTT_HOST, String(MQTT_PORT).toInt());

  #if MQTT_CREDENTIALS
    // If your broker requires authentication (username and password), set them below
    mqttClient.setCredentials(MQTT_USER, MQTT_PASS);
  #endif
  DUMPSLN("MQTT Init...");
}
