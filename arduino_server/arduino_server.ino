#include "ArduinoServer.h"


const unsigned int led = 9;
//
//class ArduinoServer {
//  private:
//
//    // buffers for receiving and sending data
//
//    // An EthernetUDP instance to let us send and receive packets over UDP
//    EthernetUDP Udp;
//
//
//  public:
//    void init() {
//      Ethernet.begin(mac, ip);
//      Udp.begin(localPort);
//    }
//    void respond() {
//      // send a reply to the IP address and port that sent us the packet we received
//      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//      Udp.write(ReplyBuffer);
//      Udp.endPacket();
//    }
//
//    void set_on_request_callback(call_back callback){
//        on_request = callback;
//      }
//
//    void run() {
//      int packetSize = Udp.parsePacket();
//      if (packetSize) {
//        // save sender IP
//        IPAddress remote = Udp.remoteIP();
//        // save sender port
//        long port = Udp.remotePort();
//        // save msg
//        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
//        // callback
//        if (on_request != NULL) {
//          on_request(remote, port, packetBuffer);
//          respond();
//        }
//        //
//        memset(packetBuffer, 0, sizeof(packetBuffer));
//      }
//    }
//};

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

