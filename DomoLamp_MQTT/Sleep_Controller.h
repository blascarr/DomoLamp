#if SLEEPMODE
  Ticker sleepReconnectTimer;
  Ticker sleepScheduler;
  Ticker wifiSleepScheduler;
  Ticker wifiWakeScheduler;
  
  void (*sleep_ptr)();
  
  void set_sleep(){
    DUMPLN("Set Sleep \t Time : ",  millis() );
  }
  
  void set_deepsleep(){
    DUMPLN("I am going to sleep\t Time : ", millis() );
    WiFi.forceSleepBegin();
    DUMPSLN("WiFi is down");
    //ESP.deepSleep( TIME_TO_SLEEP );
    #if defined(ESP32)
      esp_sleep_enable_timer_wakeup( TIME_TO_WAKE  );
      //esp_light_sleep_start();
    #endif
  }
  
  void wifi_wake(){
    DUMPLN("I am going to wake\t Time : ", millis() );
    WiFi.forceSleepWake();
    DUMPSLN("WiFi is Up");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DUMPS(".");
      }
    
      // Debugging - Output the IP Address of the ESP8266
      DUMPSLN("WiFi connected");
      DUMPLN("IP address: ", WiFi.localIP());
     //sleep_ptr = wifi_sleep;
     wifiSleepScheduler.once( SLEEP_SCHEDULE, sleep_ptr );
  }
  
  void wifi_sleep(){
    DUMPLN("I am going to sleep\t Time : ", millis() );
    WiFi.forceSleepBegin();
    DUMPSLN("WiFi is down");
    //sleep_ptr = wifi_wake;
    //wifiWakeScheduler.once( 20, wifi_wake );
  }

  void sleep_init(){
      DUMPSLN("Sleep Init: ");
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
        case ESP_SLEEP_WAKEUP_EXT0 : DUMPSLN("Wakeup caused by external signal using RTC_IO"); break;
        case ESP_SLEEP_WAKEUP_EXT1 : DUMPSLN("Wakeup caused by external signal using RTC_CNTL"); break;
        case ESP_SLEEP_WAKEUP_TIMER : DUMPSLN("Wakeup caused by timer"); break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD : DUMPSLN("Wakeup caused by touchpad"); break;
        case ESP_SLEEP_WAKEUP_ULP : DUMPSLN("Wakeup caused by ULP program"); break;
        default : DUMPF("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
      }
    }
  #endif
#endif
