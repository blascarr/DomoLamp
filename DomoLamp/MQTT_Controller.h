#include <AsyncMqttClient.h>
Ticker mqttReconnectTimer;

AsyncMqttClient mqttClient;

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
  if( !mqttClient.connected()){
    Serial.println("Invalid MQTT Credentials\n");
  }
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  mqttClient.subscribe(MQTT_TOPIC,0);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);
  Serial.print(" Payload: ");
  Serial.println( payload );
  char messageArray[len];
  memcpy ( messageArray, payload, len );
  String message(messageArray);
  Serial.println( message );
  strip.setStatus( message );
}

void MQTT_init(){
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.onMessage(onMqttMessage);

  strncpy(MQTT_HOST, custom_mqtt_server.getValue(), sizeof(MQTT_HOST));
  strncpy(MQTT_PORT, custom_mqtt_port.getValue(), sizeof(MQTT_PORT));
  strncpy(MQTT_USER, custom_mqtt_user.getValue(), sizeof(MQTT_USER));
  strncpy(MQTT_PASS, custom_mqtt_pass.getValue(), sizeof(MQTT_PASS));
  
  mqttClient.setServer(MQTT_HOST, String(MQTT_PORT).toInt());
  // If your broker requires authentication (username and password), set them below
  mqttClient.setCredentials(MQTT_USER, MQTT_PASS);
}
