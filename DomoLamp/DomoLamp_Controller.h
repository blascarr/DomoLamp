#include <Adafruit_NeoPixel.h>

enum modes { UNDEF, COLOR, BLINK, UPDOWN, RAINBOW, FADE, UPWAVE, DWAVE, LANDING, UPLANDING, DOWNLANDING, ONWIFI, NOWIFI, OFF };
enum landing_modes { UPANDDOWN, UP, DOWN };

#if NOTIFY 
  enum notif_lights : uint32_t { NOTIF_RED = 16711680, NOTIF_GREEN = 65280, NOTIF_BLUE = 255, NOTIF_WHITE = 16777215, NOTIF_PURPLE= 16711808, NOTIF_YELLOW = 13158400 };
#endif

struct colorRGB{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct statusLamp{
  uint32_t color;
  colorRGB RGBColor;
  uint16_t latency;
  uint8_t landingleds = 1;
  uint8_t bright = DEFAULT_BRIGHTNESS;
  modes effect;
  String mode;
};

class DomoLamp  : public Adafruit_NeoPixel {
    public:

      typedef void ( *_f_Strip )( );
      int brightness = DEFAULT_BRIGHTNESS;
      int fade_brightness = DEFAULT_BRIGHTNESS;
      uint8_t fade_increment = 10;
      String state;
      int pixelCycle = 0;   // Pattern Pixel Cycle in Rainbow Mode
      uint32_t color;
      long blink_millis;
      long rainbow_millis;
      statusLamp currentStatus;
      bool even = true;
      
      //LANDING MODE
      landing_modes landingMode = UP;
      uint16_t currentPixel = 0;
      uint16_t landingleds = 2;
      
      void resetWifiManager();
      typedef void ( DomoLamp::*_f_lamp )();
      _f_lamp light = &DomoLamp::idle; // Loop Controller Function
      
      DomoLamp( uint16_t n, uint16_t pin , neoPixelType type=NEO_GRB+NEO_KHZ800) : Adafruit_NeoPixel( n, pin, type ){
        this->currentStatus.color = this->Color( 0, 255, 0);
        even = !n%2;
      }
      void init(){
        this->begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
        this->reset();           // SET GND to HIGH in order to avoid current overflow          
        this->clean();           // Turn OFF all pixels ASAP
        this->setBrightness(brightness); // Set BRIGHTNESS to about 1/5 (max = 255)
        digitalWrite(POWERCONTROL_PIN, LOW);  //SET GND to LOW connecting strip voltage 

        #if NOTIFY
          this->fill( NOTIF_GREEN , 0, NOTIFY_LEDS );
          this->show(); 
        #endif
      }

      void reset(){
        digitalWrite(LED_PIN, LOW);
        digitalWrite(POWERCONTROL_PIN, HIGH);
      }

      void clean(){
        this->clear();
        this->show();
      }
      
      void loop(){
        (this->*light)();
      }

      uint32_t Wheel(byte WheelPos) {
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85) {
          return this->Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        if(WheelPos < 170) {
          WheelPos -= 85;
          return this->Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        WheelPos -= 170;
        return this->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      }

      // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
      void rainbow() {
        if( millis() - rainbow_millis >= this->currentStatus.latency ){
          rainbow_millis = millis();
          for(uint16_t i=0; i < this->numPixels(); i++) {
            this->setPixelColor(i, Wheel((i + pixelCycle) & 255)); //  Update delay time  
          }
          this->show();                             //  Update strip to match
          pixelCycle++;                             //  Advance current cycle
          if(pixelCycle >= 256)
            pixelCycle = 0;                         //  Loop the cycle back to the begining
          }        
      }

      void setStatus( String payload ){
         //DUMP("Set status from JSON: ", payload );
         JSONVar domoJSON = JSON.parse(payload);
         if (JSON.typeof(domoJSON) == "undefined") {
            DUMPSLN("Parsing input failed!");
            return;
          }
         
         if (domoJSON.hasOwnProperty("effect")) {
            int len = STREAM_CHARLENGTH;
            char messageArray[len];
            memcpy ( messageArray, (const char*)domoJSON["effect"], len );
            String message(messageArray);
            this->currentStatus.mode = message;
            DUMPS("MODE: ");
            setStatusLamp( this->currentStatus.mode );
         }

         if (domoJSON.hasOwnProperty("latency")) {
            this->currentStatus.latency = (int) domoJSON["latency"];
            DUMPLN("Latency : ", this->currentStatus.latency);
         }

         if (domoJSON.hasOwnProperty("RGBColor")) {
            this->currentStatus.RGBColor.red = (int) domoJSON["RGBColor"][0];
            this->currentStatus.RGBColor.green = (int) domoJSON["RGBColor"][1];
            this->currentStatus.RGBColor.blue = (int) domoJSON["RGBColor"][2];
            this->currentStatus.color = this->Color( this->currentStatus.RGBColor.red , this->currentStatus.RGBColor.green, this->currentStatus.RGBColor.blue );
            DUMPLN("Color : ", this->currentStatus.color);
         }
         
         if (domoJSON.hasOwnProperty("landingleds")) {
            this->currentStatus.landingleds = (int) domoJSON["landingleds"];
            DUMPLN("LANDINGLEDS: ",this->currentStatus.landingleds);
         }
         if (domoJSON.hasOwnProperty("brightness")) {
            this->setBrightness( map ( (int) domoJSON["brightness"] , 0, 100, 0 , 255) ); // Set BRIGHTNESS to about 1/5 (max = 255)
            DUMPLN("Brightness : ", this->getBrightness() );
         }
         
         setLamp();
         DUMPPRINTLN();
      }
      
      void setStatusLamp( String mode ){
        if( mode.indexOf("BLIN") == 0 ){
           this->currentStatus.effect = BLINK;
           DUMPSLN("BLINK");
        }
        if( mode.indexOf("COLO") == 0 ){
           this->currentStatus.effect = COLOR;
           DUMPSLN("COLOR");
        }
        if( mode.indexOf("RAIN") == 0 ){
           this->currentStatus.effect = RAINBOW;
           DUMPSLN("RAINBOW");
        }
        if( mode.indexOf("FADE") == 0 ){
           this->currentStatus.effect = FADE;
           DUMPSLN("FADE");
        }
        if( mode.indexOf("UPDO") == 0 ){
           this->currentStatus.effect = UPDOWN;
           DUMPSLN("UPDOWN");
        }
        if( mode.indexOf("LAND") == 0 ){
           this->currentStatus.effect = LANDING;
           DUMPSLN("LANDING");
        }
        if( mode.indexOf("UPLA") == 0 ){
           this->currentStatus.effect = UPLANDING;
           DUMPSLN("UPLANDING");
        }
        if( mode.indexOf("DOWN") == 0 ){
           this->currentStatus.effect = DOWNLANDING;
           DUMPSLN("DOWNLANDING");
        }
        if( mode.indexOf("DWAV") == 0 ){
           this->currentStatus.effect = DWAVE;
           DUMPSLN("DWAVE");
        }
        if( mode.indexOf("UPWA") == 0 ){
           this->currentStatus.effect = UPWAVE;
           DUMPSLN("UPWAVE");
        }
        if( mode.indexOf("NOWI") == 0 ){
           this->currentStatus.effect = NOWIFI;
           DUMPSLN("WIFI MANAGER RESET");
        }
        if( mode.indexOf("ONWI") == 0 ){
           this->currentStatus.effect = ONWIFI;
           DUMPSLN("WIFI ON");
        }
        if( mode.indexOf("OFF") == 0 ){
           this->currentStatus.effect = OFF;
           DUMPSLN("OFF");
        }
        if( mode.indexOf("UNDE") == 0 ){
           this->currentStatus.effect = UNDEF;
           DUMPSLN("UNDEF");
        }
      }

      void setLamp(){
        switch (this->currentStatus.effect) {
          case COLOR:
            light = &DomoLamp::colorLamp;
            break;
          case BLINK:
            light = &DomoLamp::blink;
            this->fill( this->currentStatus.color , 0 , this->numPixels());
            this->show();
            blink_millis = millis();
            break;
          case RAINBOW:
            light = &DomoLamp::rainbow;
            break;
          case FADE:
            fade_brightness = brightness;
            light = &DomoLamp::fadeIn;
            break;
          case LANDING:
            landingMode = UPANDDOWN;
            initLanding();
            light = &DomoLamp::landing;
            break;
          case UPDOWN:
            landingMode = UPANDDOWN;
            initLanding();
            light = &DomoLamp::landing;
            break;
          case UPLANDING:
            landingMode = UP;
            initLanding();
            light = &DomoLamp::landing;
            break;
          case DOWNLANDING:
            landingMode = DOWN;
            initLanding();
            light = &DomoLamp::landing;
            break;          
          case UPWAVE:
            landingMode = UP;
            initLanding();
            light = &DomoLamp::wave;
            break;
         case DWAVE:
            landingMode = DOWN;
            initLanding();
            light = &DomoLamp::wave;
            break;
          case ONWIFI:
            this->currentStatus.color = this->Color( 0 , 0, 0 );
            light = &DomoLamp::wifion;
            break;
          case NOWIFI:
            this->currentStatus.color = this->Color( 0 , 0, 0 );
            light = &DomoLamp::wifioff;
            break;
          case OFF:
            this->clear();
            this->show();
            light = &DomoLamp::idle;
            break;
          default:

            break;
          }
      }

      /////////////////////////////////////////////////
      /////////////////////////////////////////////////

      void colorLamp( ){
        this->fill( this->currentStatus.color , 0 , this->numPixels());
        this->show();
        light = &DomoLamp::idle;
      }

      void blink(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          this->clear();
          this->show();
          blink_millis = millis();
          light = &DomoLamp::unblink;
        }
      }

      void unblink(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          this->fill( this->currentStatus.color , 0 , this->numPixels());
          this->show();
          blink_millis = millis();
          light = &DomoLamp::blink;
        }
      }

      void landing(){
        
        if( millis() - blink_millis >= this->currentStatus.latency ){
          
          this->setPixelColor(currentPixel, 0 );
          this->setPixelColor(this->numPixels() - currentPixel, 0 );
          blink_millis = millis();

          if( landingMode == UPANDDOWN  ){
            // This is a trick, because, we loop over numPixels which is two times larger, 
            // Result will be up and down
            currentPixel++;
            if( currentPixel >= this->numPixels() ){
              currentPixel = 0;
            }
          }

          if( landingMode == UP  ){
            currentPixel++;
            if( currentPixel >= this->numPixels()/2 ){
              currentPixel = 0;
            }
          }

          if( landingMode == DOWN  ){
            currentPixel--;
            // Second condition avoids init values from zero to 65545 due to uint 
            if( currentPixel == 0 || currentPixel >= this->numPixels() ){
              currentPixel = this->numPixels()/2;
            }
          }
          this->setPixelColor(this->numPixels() - currentPixel, this->currentStatus.color );
          this->setPixelColor(currentPixel, this->currentStatus.color );
          this->show();
        }
      }

      void wave(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
           blink_millis = millis();
          int dir = 1;
          if( landingMode == UP  ){
            currentPixel++;
            dir = 1;
            if( currentPixel >= this->numPixels()/2 ){
              currentPixel = 0;
            }
          }
          
          if( landingMode == DOWN  ){
            currentPixel--;
            dir = -1;
            if( currentPixel == 0 || currentPixel >= this->numPixels() ){
              currentPixel = this->numPixels()/2;
            }
          }
          for(uint16_t i=currentPixel%landingleds; i <= this->numPixels()/2; i=i+landingleds) {
              this->setPixelColor( i - dir , 0 );
              this->setPixelColor(this->numPixels() - i - dir, 0 );
            
              this->setPixelColor(i, this->currentStatus.color);
              this->setPixelColor(this->numPixels() - i, this->currentStatus.color );
          }
          this->show();
        }
      }

      void initLanding(){
        currentPixel = 0;
        this->clear();
      };

      void fadeIn(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          fade_brightness += fade_increment;
          this->fill( this->currentStatus.color , 0 , this->numPixels());
          if ( fade_brightness > 255 ) { light = &DomoLamp::fadeOut; return; }
          this->setBrightness(fade_brightness);
          this->show();
          blink_millis = millis();
        }
      }
      
      void fadeOut(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          fade_brightness -= fade_increment;
          this->fill( this->currentStatus.color , 0 , this->numPixels());
          if ( fade_brightness < 0 ) { light = &DomoLamp::fadeIn; return; }
          this->setBrightness(fade_brightness);
          this->show();
          blink_millis = millis();
        }
      }

      void wifioff(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          blink_millis = millis();
          DomoLamp::resetWifiManager();
          light = &DomoLamp::blink;
        }
      };

      void wifion(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          blink_millis = millis();
          DUMPSLN("ON Wifi Control");
          light = &DomoLamp::blink;
        }
      };
      
      void idle(){
        if( millis() - blink_millis >= this->currentStatus.latency ){
          blink_millis = millis();
        }
      };
};
