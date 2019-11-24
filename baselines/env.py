import gym
from gym import spaces
from gym.utils import seeding
import numpy as np
import time
import random
from array import array
import sys
from actionmodule import ActionModule
from visionmodule import VisionModule
from gamemodule import GameModule
from debugmodule import DebugColor,DebugModule
TARGET_AXIS_MAX = 3
def random2axis(r):
    return (r-0.5)*2*3

class Env(gym.Env):
    _feedback = None
    target_pos_x = 0
    target_pos_y = 0
    def __init__(self):
        self.low_action = np.array([-1,-1,-1])
        self.high_action = np.array([1,1,1])
        self.action_space = spaces.Box(low=self.low_action, high=self.high_action, dtype=np.float32)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(14,), dtype=np.float32)
        self.am = ActionModule()
        self.vm = VisionModule()
        self.gm = GameModule()
        self.dm = DebugModule()
        self.am.reset()
        time.sleep(0.1)
    def step(self, action=[0,0,0]):
        self.gm.sendCommand([action[0],0,0],self.vm.me_angle,self._feedback)
        self._feedback = self.vm.get_feedback([self.target_pos_x,self.target_pos_y],action)
        return self._feedback
    def reset(self):
        self.target_pos_x = random2axis(random.random())
        self.target_pos_y = random2axis(random.random())
        target = [self.target_pos_x,self.target_pos_y]
        self.vm.reset()
        self.am.reset()
        time.sleep(0.1)
        self.am.reset()
        self.dm.gui_debug_x(target)
        self.dm.send()
        time.sleep(0.1)
        self._feedback = self.vm.get_feedback(target,[0,0,0])
        return self._feedback[0]

if __name__ == '__main__':
    env = Env()
    env.reset()
    while True:
        time.sleep(0.013)
        env.step()
