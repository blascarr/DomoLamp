#include <DNSServer.h>

#include <ESPAsyncWebServer.h>
#include "webpage.h"

AsyncWebServer server(80);
DNSServer dns;

// Create an Event Source on /events
AsyncEventSource events( SERVER_EVENTS_ENDPOINT );

void initWebServer() {
  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", domolamp_html);
  });

   server.on( SERVER_ENDPOINT , HTTP_GET, [] (AsyncWebServerRequest *request) {  
    if (request->hasParam( DATA_REQUEST_INPUT )){
      String jsonData = request->getParam("LampData")->value();
      Serial.print(" JSON Data ");
      Serial.println( jsonData );
      strip.setStatus(jsonData);
      request->send(200, "text/plain", "OK");
    }
  });

   // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
        Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    Serial.print("On Connect Event ");
    //events.send(getNodeInfo().c_str(), "node_info", millis());
  });
  
  server.addHandler(&events);
  server.begin();
}
