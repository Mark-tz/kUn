import socket
import time
from game_A2M_pb2 import *
from pymunk.vec2d import Vec2d
import math
AXIS_RATIO = 32000
AXIS_D_RATIO = 20000
def regularButton(num):
    if num > 0:
        return 1
    return 0
def regularAxis(num):
    return num*AXIS_RATIO
def regularDAxis(num):
    return num*AXIS_D_RATIO
def limitValue(v,minV,maxV):
    if v <= minV:
        return minV
    if v >= maxV:
        return maxV
    return v

class GameModule:
    def __init__(self,PORT = 20012,IP = '127.0.0.1'):
        self.address = (IP,PORT)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.start_time = time.time()
    def sendCommand(self,arr,me_angle,last_fb):
        cmds = Game_Commands()
        cmds.start = True
        cmds.isKey = False
        cmd = cmds.command_joy.add()
        cmd.robot_id = 0
        cmd.time = int((time.time() - self.start_time)*1000)

        cmd.button_y = 0
        cmd.button_b = 0
        cmd.button_x = 0
        cmd.button_rb = 0
        cmd.button_lo = 0
        cmd.button_ro = 0
        cmd.button_start = 0
        cmd.button_back = 0
        cmd.button_home = 0

        cmd.axis_lt = 0
        cmd.axis_rt = 0
        cmd.axis_xx = 0
        cmd.axis_yy = 0

        cmd.button_a = 0 # int(regularButton(arr[0]))

        target = Vec2d(last_fb[0][0],last_fb[0][1])
        pos = Vec2d(last_fb[0][-3],last_fb[0][-2])
        toTarget = target - pos
        controller_x = toTarget.x/toTarget.length
        controller_y = toTarget.y/toTarget.length

        cmd.axis_lx  = int(limitValue(regularAxis(controller_x) + regularDAxis(arr[1]),-AXIS_RATIO,AXIS_RATIO))
        cmd.axis_ly  = -int(limitValue(regularAxis(controller_y) + regularDAxis(arr[2]),-AXIS_RATIO,AXIS_RATIO))

        target_angle = me_angle + arr[0]*math.pi/2.0
        # print("markdebug : ",target_angle - me_angle)
        cmd.axis_rx  = int(regularAxis(math.cos(target_angle)))# int(regularAxis(arr[3]))
        cmd.axis_ry  = -int(regularAxis(math.sin(target_angle)))# int(regularAxis(arr[4]))
        # print("markdebug : ",cmd.axis_rx-int(regularAxis(math.cos(target_angle))),cmd.axis_ry+int(regularAxis(math.sin(target_angle))),target_angle)
        cmd.button_lb = 0

        self.socket.sendto(cmds.SerializeToString(), self.address)

if __name__ == '__main__':
    pass