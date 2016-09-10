So simple code to interface

After downloading/cloning the source code to your local machine
 - Create an empty python script file

```python
from  pythonclient import SimplePythonClient

def callback(response_data):
  print response_data
  
client = SimplePythonClient(addr='192.168.1.5', port=5000)
client.on_response = callback
client.send_msg(msg='on')
```

the above code will initialize the client and will send the msg to the specified address target 

 - arduinosertver.ino in the arduino_server folder
 
```cpp
 #include "ArduinoServer.h"


const unsigned int led = 9;

// Modify the mac, IPAddress localPort with your values

byte mac[6] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip = IPAddress(192, 168, 1, 6);

unsigned int localPort = 8888;      // local port to listen on


ArduinoServer ard;

void setup() {
  // will bind a callback function when request received
  ard.set_request_callback(on_receive);
  // initialize the server on the specified port & ip
  ard.init(mac, ip, localPort);

  pinMode(led, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  ard.run();
  delay(10);
}

bool state = false;

// Modify the content of the function with your implementation 

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

```
 
 the above code will initialize the UDP server and listen to coming requests 
 then it will do the bounded callbacks (LED ON/OFF) in our example, and generate a response for the client
