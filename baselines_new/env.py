import gym
from gym import spaces
from gym.utils import seeding
import numpy as np
import time
from array import array
import sys
from actionmodule import ActionModule
from visionmodule import VisionModule
from gamemodule import GameModule
class Env(gym.Env):
    def __init__(self):
        self.low_action = np.array([-1,-1,-1])
        self.high_action = np.array([1,1,1])
        self.action_space = spaces.Box(low=self.low_action, high=self.high_action, dtype=np.float32)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(6,), dtype=np.float32)
        self.am = ActionModule()
        self.vm = VisionModule()
        self.gm = GameModule()
        self.am.reset()
        time.sleep(0.1)
    def step(self, action=[0,0,0]):
        self.gm.sendCommand(action,self.vm.me_angle)
        feedback = self.vm.get_feedback(action)
        return feedback
    def reset(self):
        self.vm.reset()
        self.am.reset()
        time.sleep(0.1)
        self.am.reset()
        obs, _, _, _ = self.vm.get_feedback([0,0,0])
        return obs

if __name__ == '__main__':
    env = Env()
    while True:
        time.sleep(0.013)
        env.step([1.0])
