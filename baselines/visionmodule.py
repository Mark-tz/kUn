# -*- coding: utf-8 -*-

import socket
from time import sleep
import vision_detection_pb2 as detection
from pymunk.vec2d import Vec2d
import math
from statusmodule import StatusModule
ME = 0
ENEMY = 0
# ENEMY2 = 1

BLUE_STATUS_PORT = 60011
YELLOW_STATUS_PORT = 60012

OUTSIDE_X = 4000
OUTSIDE_Y = 4000

class VisionModule:
    me_angle = 0
    me_infrared = 0
    def __init__(self, VISION_PORT=41001, SENDERIP = '0.0.0.0'):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        self.sock.bind((SENDERIP,VISION_PORT))
        self.bs = StatusModule(BLUE_STATUS_PORT)
        self.ys = StatusModule(YELLOW_STATUS_PORT)

    def outside(self,pos):
        return (math.fabs(pos.x) > OUTSIDE_X or math.fabs(pos.y) > OUTSIDE_Y)

    def receive(self):
        data, _ = self.sock.recvfrom(65535)
        sleep(0.0005) # wait for reading
        return data
    def reset(self):
        self.me_angle = 0
        self.me_infrared = 0
    # def get_angle(self):
    #     self.me_angle = 
    def get_feedback(self,target,action):
        me = None
        enemy = None
        # enemy2 = None
        ball = None
        while True:
            data = self.receive()
            package = detection.Vision_DetectionFrame()
            package.ParseFromString(data)
            # print(package.ByteSize())
            robots = package.robots_blue # repeat
            for robot in robots:
                if robot.robot_id == ME:
                    me = robot
                    break
            robots = package.robots_yellow
            for robot in robots:
                if robot.robot_id == ENEMY:
                    enemy = robot
                # if robot.robot_id == ENEMY2:
                #     enemy2 = robot
            ball = package.balls # not repeat
            if me is None or enemy is None or ball is None:
                continue

            self.me_angle = me.raw_orientation
            self.me_infrared = self.bs.getInfrared(ME)
            # me = Vec2d(me.raw_x/1000.0,me.raw_y/1000.0)
            # enemy = Vec2d(enemy.raw_x/1000.0,enemy.raw_y/1000.0)

            # enemy2 = Vec2d(enemy2.raw_x/1000.0,enemy2.raw_y/1000.0)
            # ball = Vec2d(ball.raw_x/1000.0,ball.raw_y/1000.0)
            # me2enemy = enemy - me
            # me2enemy2 = enemy2 - me
            # me2ball = ball - me
            # enemyDir = me2enemy.angle/math.pi
            # enemyDist = me2enemy.length/7.0
            # enemy2Dir = me2enemy2.angle/math.pi
            # enemy2Dist = me2enemy2.length/7.0
            # ballDir = me2ball.angle/math.pi
            # ballDist = me2ball.length/7.0
            # print(ballDir)
            reward = -1
            done = False
            # getBall = -1
            if self.outside(me):
                # reward -= 1000
                # print("outside")
                done = True
            if self.bs.getInfrared(ME) != 1 :
                if self.outside(ball):
                    done = True
                else:
                    continue
                # getBall = 1
                reward = 0
            if self.ys.getInfrared(ENEMY) == 1:
                # reward -= 1000
                # print("enemygetball")
                done = True
            target_pos =  Vec2d(target[0],target[1])
            ball = Vec2d(ball.raw_x/1000.0,ball.raw_y/1000.0)
            toTarget = target_pos - ball
            if toTarget.length<1:
                reward += 500
                done = True
            reward -= math.fabs(action[0])*0.5
            reward += 1/toTarget.length*2
            # print("markdebug : ",done)
            return [target[0],target[1],enemy.raw_x/1000.0,enemy.raw_y/1000.0,enemy.raw_orientation,me.raw_x/1000.0,me.raw_y/1000.0,me.raw_orientation], reward, done, {}

if __name__ == '__main__':
    vision = VisionModule()
    while True:
        # print(vision.get_feedback())
        # vision.get_feedback([0])
        pass