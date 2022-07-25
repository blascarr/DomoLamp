#include <DNSServer.h>

#include <WiFiUdp.h>
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

   // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      //#ifdef SERIALDEBUG
        Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
      //#endif
    }
    Serial.print("On Connect Event ");
    //events.send(getNodeInfo().c_str(), "node_info", millis());
  });
  
  server.addHandler(&events);
  server.begin();
}
