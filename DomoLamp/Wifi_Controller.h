#if defined(ESP32)
  #include <WiFi.h>
  #include <mDNS.h>
#endif

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

#if defined(ESP8266)
  WiFiEventHandler wifiConnectHandler;
  WiFiEventHandler wifiDisconnectHandler;
#endif

Ticker wifiReconnectTimer;

bool connectToWifi() {
  bool connected = false;
  DUMPSLN("Wi-Fi ...");
  WiFi.mode(WIFI_STA);
  #if WIFIMANAGER 
    DUMPSLN("Connecting to WifiManager...");
    wifiManager.addParameter(&custom_sleep);

    if(!domolampTicker.active() ){
      DUMPSLN("Ticker Domolamp Init ");
      domolampTicker.attach_ms( time_interval, striploop );
    }
    
    #if NOTIFY
          strip.clean();
          strip.fill( NOTIF_BLUE , 0, 2*NOTIFY_LEDS );
          strip.show(); 
    #endif
    
    bool wifiManagerConnected = wifiManager.autoConnect(WIFI_HOST);
    
    if( wifiManagerConnected ){
        DUMPSLN("Async WifiManager On");
        DUMPS("Connected to Wifi - Local IP : ");
        // Configures static IP address
        if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, PRIMARYDNS, SECONDARYDNS)) {
          DUMPSLN("STA Failed to configure");
          #if NOTIFY
            strip.clean();
            strip.fill( NOTIF_RED , 0, 2*NOTIFY_LEDS );
            strip.show(); 
          #endif
        }else{
          connected = true;
        }
    }
    else {
        DUMPSLN("Configportal running");
    }
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      DUMPSLN("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }
  #else
    WiFi.begin( WIFI_SSID, WIFI_PASS );
    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, PRIMARYDNS, SECONDARYDNS)) {
      DUMPSLN("STA Failed to configure");
      #if NOTIFY
        strip.clean();
        strip.fill( NOTIF_PURPLE, 0, 2*NOTIFY_LEDS );
        strip.show(); 
      #endif
    }
    DUMPSLN("Connecting to Wifi...");
    while (WiFi.status() != WL_CONNECTED) {
      DUMPS(".");
      delay(1000);
    }
    connected = true;
  #endif
  
  if( connected ){
    #if NOTIFY
      strip.clean();
      strip.fill( NOTIF_WHITE, 0, 2*NOTIFY_LEDS );
      strip.show(); 
    #endif
    DUMPLN("Wifi Connected - Local IP : ",WiFi.localIP());
  } 
  return connected;
}
