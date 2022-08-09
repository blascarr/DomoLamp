#if SLEEPMODE
  Ticker sleepReconnectTimer;
  Ticker sleepScheduler;
  Ticker wifiSleepScheduler;
  Ticker wifiWakeScheduler;
  
  void (*sleep_ptr)();
  
  void set_sleep(){
    Serial.print("I am going to say something \t Time : ");
    Serial.println( millis() );
  }
  
  void set_deepsleep(){
    Serial.print("I am going to sleep\t Time : ");
    Serial.println( millis() );
    WiFi.forceSleepBegin();
    Serial.println("WiFi is down");
    //ESP.deepSleep( TIME_TO_SLEEP );
    #if defined(ESP32)
      esp_sleep_enable_timer_wakeup( TIME_TO_WAKE  );
      //esp_light_sleep_start();
    #endif
  }
  
  void wifi_wake(){
    Serial.print("I am going to wake\t Time : ");
    Serial.println( millis() );
    WiFi.forceSleepWake();
    Serial.println("WiFi is Up");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
    
      // Debugging - Output the IP Address of the ESP8266
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
     //sleep_ptr = wifi_sleep;
     wifiSleepScheduler.once( SLEEP_SCHEDULE, sleep_ptr );
  }
  
  void wifi_sleep(){
    Serial.print("I am going to sleep\t Time : ");
    Serial.println( millis() );
    WiFi.forceSleepBegin();
    Serial.println("WiFi is down");
    //sleep_ptr = wifi_wake;
    //wifiWakeScheduler.once( 20, wifi_wake );
  }

  void sleep_init(){
      Serial.println("Sleep Init: ");
      sleep_ptr = wifi_sleep;
      //wifiSleepScheduler.once(SLEEP_SCHEDULE, sleep_ptr );
      //wifiWakeScheduler.attach_ms(SLEEP_TIMER, wifi_wake );
      //sleepReconnectTimer.attach_ms(SLEEP_TIMER, set_sleep );
      //sleepScheduler.once( SLEEP_SCHEDULE, set_deepsleep );
      
      #if defined(ESP32)
        print_wakeup_reason();
      #endif
  }

  #if defined(ESP32)
    void print_wakeup_reason(){
      esp_sleep_wakeup_cause_t wakeup_reason;
    
      wakeup_reason = esp_sleep_get_wakeup_cause();
    
      switch(wakeup_reason)
      {
        case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
        case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
        case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
        default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
      }
    }
  #endif
#endif
