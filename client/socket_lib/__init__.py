import socket

class ClientSocket:
    """
    simple client socket for omnomnom game
    """
    
    def __init__(self):
        """
        creates a socket and starts a connection
        """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.PORT = 2222
        # connect on construction,
        # use for duration of a game,
        # close connection on destruction later
        self.sock.connect(("192.168.43.67", self.PORT))

    def __del__(self):
        """
        close the connection on destruction
        """
        self.sock.shutdown()
        self.sock.close()

    def send(self, msg):
       """
       sends a general message given by the user

       base for code borrowed from https://docs.python.org/3.6/howto/sockets.html
       """
       # keep track of the total sent
       # so we can make sure the whole message is sent
       msg = (msg+'\n').encode('utf-8')
       totalsent = 0
       while totalsent < len(msg):
           sent = self.sock.send(msg[totalsent:])
           # it is bad if we still have things to send
           # but do not send anything
           if sent == 0:
               raise RuntimeError("connection broken")
           totalsent += sent
       
    #############################################
    # functions to send specific input messages #
    #############################################
    
    # first, directions

    def sendLeft(self):
        self.send("left")

    def sendRight(self):
        self.send("right")

    def sendUp(self):
        self.send("up")

    def sendDown(self):
        self.send("down")

    # om nom nom nom nom nom nom nom nom nom nom nom nom nom nom nom nom nom

    def sendNom(self):
        self.send("nom")
