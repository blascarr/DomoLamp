# DomoLamp
**DomoLamp** is an open source **IOT lamp** controlled with a **MQTT server** which could be connected with any other API platform, such as Twitter, Instagram, Facebook or any other API on your own.
Also can be connected with **Node-Red** Server in order to define some other complex logic behavior.

![LampModel.PNG](/src/LampModel.png)

## Purpose Idea

The original idea is used to **express emotions** with different colours and effects for eduational purposes with kids. Also used if adults and kids lives far away from each other.

At first, the lamp represents the emotion of an adult ( controlled through a webpage ) in order to express adults feelings for kids to learn that big people can feel the same.

- **GREEN** → **Relaxed**
- **BLUE** → **Sadness**
- **RED** → **Angry**
- **YELLOW** → **Happiness**
- **PINK**→ **In Love**
- **PURPLE** → **Fear**
- **ORANGE** → **Excitement**
- **SEA** → **Creative**
- **WHITE** → *Used for Configuration*

![DomoLampSketch.PNG](/src/DomoLampSketch.png)

## BOM ( Bill of Materials)

- ESP module ( Wemos )
- [Neopixel Leds](https://www.aliexpress.com/item/4000113154702.html) ( 5V, IP65, Indexed 2812 )
- [LiPo Battery 3.7V](https://es.aliexpress.com/item/1005002919536938.html) **2000mAh**
- Battery Charger
    - [Model DC Step-Up 18650](https://www.aliexpress.com/item/32986165837.html) ( Vout regulator )
    - [Model **18650 TP4056](https://www.aliexpress.com/item/32930640893.html) (** Vout 5V )
- [Rocker Switch](https://www.aliexpress.com/item/32979907338.html)
- [JST Connector](https://www.aliexpress.com/item/32954379535.html)
- PLA 3D Print plastic
    - Transparent PLA for **DomoLamp** piece
    - Any other colour for the rest.

## Print Recommendations

Use **Spiralize Outer Contour** in **Ultimaker Cura** Software to print the lamp with transparent colour with a thin layer in order to print it reflective for LED lights.  

![SpiralizeLamp.png](/src/SpiralizeLamp.png)

## Libraries Required

- [ESP Async WifiManager](https://github.com/khoih-prog/ESPAsync_WiFiManager)
- [ArduinoJSON](https://arduinojson.org/)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [AsyncMqttClient](https://github.com/marvinroger/async-mqtt-client)
- [Ticker](https://github.com/sstaub/Ticker)
- [ArduinoOTA](https://github.com/jandrassy/ArduinoOTA)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- ESP8266
    - ESP8266WiFi
- ESP32

## Electronic Wiring with battery charger

![DomoLamp_bb.png](/src/DomoLamp_bb.png)

## Data JSON Structure sent through Node-Red

### Simple Node-Red configuration used with MQTT Server

**Topic** configured in Node Red should be the same as in **config.h** sketch file. 

**IMPORTANT:** **retain** set to **true** for retaining last message while Lamp is disconnected. 

![NodeRed Switch MQTT Send.png](/src/NodeRed_Switch_MQTT_Send.png)

![NodeRed MQTT Out.png](/src/NodeRed_MQTT_Out.png)

### JSON Structure

```jsx
{
    "RGBColor": [
        0,
        255,
        0
    ],
    "timestamp": 1000,
    "timestop": 5000,
    "speed": 100,
    "latency": 2000,
    "effect": "COLOR"
}
```

### Node Red UI Dashboard

Dashboard configuration to create a user interface controlled webpage Domolamp with MQTT server defined in Node-Red and access to your **Node-Red** host **http:localhost:1880/ui**

[**Demo Node Red**](http://node.blascarr.com:1880/ui/) in production with **feel/domolamp** topic.

![NodeRed_DashBoard.png](/src/NodeRed_DashBoard.png)

![NodeRedDashBoardConfig.png](/src/NodeRedDashBoardConfig.png)

![NodeRedDashBoardDropDown.png](/src/NodeRedDashBoardDropDown.png)

![NodeRedDashBoardFunction.png](/src/NodeRedDashBoardFunction.png)

### Effects included

- COLOR
- BLINK
- RAINBOW
- FADE
- UPDOWN
- LANDING
    - UPLANDING
    - DOWNLANDING
- WAVE
    - UPWAVE
    - DOWNWAVE
- WIFIOFF
- OFF

## Configuration File

In **Config.h** , DomoLamp can be defined with parameters. 

DomoLamp use **WifiManager** to connect it to the local network. Configuration webpage through **192.168.4.1** IP address when a device is connected to **DOMO LAMP** network.

Just only credentials are required for **MQTT Server** and other configurations are used to select topic used in controlled with the structured explained before.

![DomoLampConfig.png](/src/DomoLampConfig.png)

## FAQ

### What can i do if Lamp doesn’t connect to my WiFi network?

If some problems with local network connection occured, you can create a previous network credentials with your phone from **adjustments** → **wireless connection** → **personal access point**.

If lamp can’t connect from other place, you can reset settings, sending **WIFIOFF** effect **through your MQTT Server**.