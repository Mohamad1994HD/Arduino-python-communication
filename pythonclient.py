import socket

class SimplePythonClient:
    def __init__(self,addr='', port=8888,response_time_out=1, on_response = None, response_size=2048):
        self.address = (addr, port)
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.connection.settimeout(response_time_out)
        #set callback response
        self.on_response = on_response
        self.response_size = response_size

    def send_msg(self, msg=''):
        self.connection.sendto(msg, self.address)
        try:
            self.on_response(self.connection.recvfrom(self.response_size))
        except socket.error, msg:
            print "Error: {0}".format(msg)

    
        
    
