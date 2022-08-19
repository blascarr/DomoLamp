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

   server.on("/domo", HTTP_GET, [] (AsyncWebServerRequest *request) {  
    //Get Name
    String jsonData = request->getParam("LampData")->value();
    Serial.print(" JSON Data ");
    Serial.println( jsonData );

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
