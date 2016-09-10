#ifndef AS
#define AS

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

typedef void (*call_back) (IPAddress ip, unsigned int port, char request_body[]);

class ArduinoServer: public EthernetUDP
{
  private:

    char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
    char  *SUCCESS = "SUCCESS";       // a string to send back
    char *ReplyMsg = "";
    char *INVALID_COMMAND = "403";
    
    call_back on_request;

  public:
    ArduinoServer(call_back callback=NULL): on_request(callback) {};

    void init(byte mac[6], IPAddress ip, unsigned int local_port);

    void generate_response(char *resp);
    void set_response_msg(char *resp);
  
    
    void set_request_callback(call_back callback);

    void run();

  };
#endif
