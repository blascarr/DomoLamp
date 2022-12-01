#include <DNSServer.h>

#include <ESPAsyncWebServer.h>
#include "webpage.h"

AsyncWebServer server( SERVER_PORT );
DNSServer dns;

// Create an Event Source on /events
AsyncEventSource events( SERVER_EVENTS_ENDPOINT );

void initWebServer() {
  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", domolamp_html);
  });

   server.on( SERVER_ENDPOINT, HTTP_GET, [] (AsyncWebServerRequest *request) {  
    if (request->hasParam( DATA_REQUEST_INPUT )){
      String jsonData = request->getParam( DATA_REQUEST_INPUT )->value();
      DUMPLN(" JSON Data ", jsonData );
      strip.setStatus(jsonData);
      request->send(200, "text/plain", "OK");
    }
  });

   // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
        DUMPF("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    DUMPSLN("On Connect Event ");
  });
  
  server.addHandler(&events);
  server.begin();
  DUMPSLN("SERVER ON");
}
