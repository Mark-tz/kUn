# -*- coding: utf-8 -*-
import socket
import time
import array
import threading
from zss_cmd_pb2 import Robots_Status,Robot_Status
ROBOT_NUM = 16
BLUE_PORT = 60011
YELLOW_PORT = 60012
class StatusModule:
    def __init__(self,PORT,IP = '127.0.0.1'):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        self.sock.bind((IP,PORT))
        self.status = array.array('i',(0 for i in range(0,ROBOT_NUM)))
        self.rec_thread = threading.Thread(target = self.receive,args = ())
        self.rec_thread.daemon = True
        self.rec_thread.start()
    
    def receive(self):
        while True:
            data, _ = self.sock.recvfrom(65535)
            time.sleep(0.001)
            self.parse(data)

    def parse(self,data):
        robot = Robot_Status()
        robot.ParseFromString(data)
        self.status[robot.robot_id] = robot.infrared

    def getInfrared(self,num):
        return self.status[num]

if __name__ == '__main__':
    smb = StatusModule(BLUE_PORT)
    smy = StatusModule(YELLOW_PORT)
    while True:
        time.sleep(0.1)
        print("yellow 0 infrared : ",smy.getInfrared(0))
