#if WIFIMANAGER 
  #include "ESPAsync_DomoManager/src/ESPAsync_DomoManager.h" 

  ESPAsync_WMParameter  custom_mqtt_server("server", "MQTT server", MQTT_HOST, 40);
  ESPAsync_WMParameter  custom_mqtt_port("port", "MQTT port", MQTT_PORT, 6);
  ESPAsync_WMParameter  custom_mqtt_topic("topicid", "MQTT topic ID", DOMOLAMP_ID, 20);
  ESPAsync_WMParameter  custom_mqtt_acktopic("acktopic", "MQTT acktopic", MQTT_ACKTOPIC, 20);
  ESPAsync_WMParameter  custom_sleep("SleepMode", "Sleep Mode", SLEEP_TIME, 20);
  #if MQTT_CREDENTIALS
    ESPAsync_WMParameter  custom_mqtt_user("user", "MQTT user", MQTT_USER, 20);
    ESPAsync_WMParameter  custom_mqtt_pass("pass", "MQTT pass", MQTT_PASS, 20);
  #endif
  ESPAsync_WiFiManager wifiManager(&server,&dns);
#endif
