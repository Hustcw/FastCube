import socket
import os
import subprocess
import signal
import re

class ControlSide(object):
    def __init__(self,ip = "192.168.4.1",port = 333):
        self.buffer_for_sending = ''
        self.first_command = ''
        self.socket = socket.socket()
        self.socket.connect((ip,port))

    def run(self):
        return subprocess.Popen('../ControlSide/algorithm/app',stdout=subprocess.PIPE)

    def send(self,_str):
        self.socket.sendall(bytes(_str, encoding="utf-8"))

    def handler(self,signum, frame):
        raise IOError("FastCube Read Error!")

    def minix(self):
        _dic = ['3','2','1']
        _red = [
            "U1R1L1U2R3L3U1L1R1U2L3R3",
        ]
        _tmp = [ x[0]+_dic[int(x[1]) - 1]  for x in re.findall('..',self.buffer_for_sending)]
        _tmp.reverse()
        _tmp.append(_red[0])
        self.first_command =  ''.join(_tmp)
        print('re1:',self.first_command)
        self.send(self.first_command+'@'+self.buffer_for_sending+'~')

    def __call__(self):
        signal.signal(signal.SIGALRM, self.handler)
        signal.alarm(3)
        try:
            p = self.run()
            self.buffer_for_sending = bytes.decode(p.communicate()[0])
            signal.alarm(0)
            print('OK:',self.buffer_for_sending)
            self.minix()
        except IOError as e:
            print('Timeout:',e)
            p.kill()
            return -1
        # self.send(self.buffer_for_sending)




if __name__ == '__main__':
    ControlSide()()
