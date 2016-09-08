

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

typedef void (*call_back) (IPAddress ip, long port, char request_body[]);

const unsigned int led = 9;

class ArduinoServer {
  private:
    byte mac[6] = {
      0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
    };
    IPAddress ip = IPAddress(192, 168, 1, 6);

    unsigned int localPort = 8888;      // local port to listen on

    // buffers for receiving and sending data
    char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
    char  ReplyBuffer[100] = "acknowledged";       // a string to send back

    // An EthernetUDP instance to let us send and receive packets over UDP
    EthernetUDP Udp;

    call_back on_request;

  public:
    void init() {
      Ethernet.begin(mac, ip);
      Udp.begin(localPort);
    }
    void respond() {
      // send a reply to the IP address and port that sent us the packet we received
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(ReplyBuffer);
      Udp.endPacket();
    }

    void set_on_request_callback(call_back callback){
        on_request = callback;
      }
      
    void run() {
      int packetSize = Udp.parsePacket();
      if (packetSize) {
        // save sender IP
        IPAddress remote = Udp.remoteIP();
        // save sender port
        long port = Udp.remotePort();
        // save msg
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        // callback
        if (on_request != NULL) {
          on_request(remote, port, packetBuffer);
          respond();
        }
        //
        memset(packetBuffer, 0, sizeof(packetBuffer));
      }
    }
};



ArduinoServer ard;

void setup() {
  // start the Ethernet and UDP:
  ard.set_on_request_callback(on_receive);
  ard.init();

  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  ard.run();
  delay(10);
}

void on_receive(IPAddress addr, long port, char msg[]) {
  Serial.println(msg);
  if (strcmp(msg, "on") == 0){
      digitalWrite(led, HIGH);
    }
  else if(strcmp(msg, "off") == 0){
      digitalWrite(led, LOW);
    }
}

