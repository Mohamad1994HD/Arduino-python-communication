#include "ArduinoServer.h"


const unsigned int led = 9;

byte mac[6] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip = IPAddress(192, 168, 1, 6);

unsigned int localPort = 8888;      // local port to listen on


ArduinoServer ard;

void setup() {
  // start the Ethernet and UDP:
  ard.set_request_callback(on_receive);
  ard.init(mac, ip, localPort);

  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  ard.run();
  delay(10);
}

bool state = false;

void on_receive(IPAddress addr, unsigned int port, char msg[]) {
  Serial.println(msg);
  if (!
      (strcmp(msg, "on") == 0 || strcmp(msg, "off") == 0)
     )
  {
    ard.set_response_msg("403");
    Serial.println("Invalid command");
    return;
  }
  
  strcmp(msg,"on")==0 ? state=true:state=false;
  digitalWrite(led, state);

  state==1 ? ard.set_response_msg("on"):ard.set_response_msg("off");
}

