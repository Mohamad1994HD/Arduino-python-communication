import socket

class SimplePythonClient(object):
    def __init__(self,addr='', port=8888,response_time_out=1, on_response = None, response_size=4096):
        self._address = (addr, port)
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.connection.settimeout(response_time_out)
        #set callback response
        self._on_response = on_response
        self._response_size = response_size

    def send_msg(self, msg=''):
        self.connection.sendto(msg, self._address)
        try:
            self._on_response(self.connection.recvfrom(self._response_size))
        except socket.error, msg:
            print "Error: {0}".format(msg)

    @property
    def address(self):
        return self._address

    @address.setter
    def address(addr, port):
        self._address = (addr,port)

        
    @property
    def response_size(self):
        return self._response_size

    @response_size.setter
    def response_size(self, val=4096):
        if val<1024:
            raise ValueError("Invalid Value")
        self._response_size = val

    @property
    def on_response(self):
        pass
    
    @on_response.setter
    def on_response(self, callback):
        self._on_response = callback 
    
    
    
    @property
    def time_out(self):
        return self.connection.gettimeout()
        
    @time_out.setter
    def time_out(self, val):
        print 'setting val'
        if val<1:
            raise ValueError("Invalid Value")
        self.connection.settimeout(val)

    
