#include "ArduinoServer.h"

void ArduinoServer::init(byte mac[6], IPAddress ip, unsigned int local_port) {
  Ethernet.begin(mac, ip);
  begin(local_port);
}

void ArduinoServer::generate_response(char *resp) {
  beginPacket(remoteIP(), remotePort());
  write(resp);
  endPacket();
}

void ArduinoServer::set_response_msg(char *resp) {
  this->ReplyMsg = resp;
  Serial.println(ReplyMsg);
}


void ArduinoServer::run() {
  int packetSize = parsePacket();
  if (packetSize) {
    // save sender IP
    IPAddress remote = remoteIP();
    // save sender port
    long port = remotePort();
    // save msg
    read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // callback
    if (on_request != NULL) {
      on_request(remote, port, packetBuffer);
    }
    
    char *rep = "";
    strcat(rep, ReplyMsg);
    strcat(rep, "::");
   
    if (strcmp(ReplyMsg, INVALID_COMMAND) == 0) {
      strcat(rep, "Invalid");
    }
    else {
      strcat(rep, SUCCESS);
    }
    
    generate_response(rep);
    //
    memset(packetBuffer, 0, sizeof(packetBuffer));
    memset(rep, 0, sizeof(rep));
  }
}

void ArduinoServer::set_request_callback(call_back callback) {
  on_request = callback;
}
