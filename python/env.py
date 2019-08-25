import gym
from gym import spaces
from gym.utils import seeding
import numpy as np
from time import sleep
from array import array
import zss_kun
import sys

class Env(gym.Env):
    def __init__(self,port):
        self.low_action = np.array([-1, -1, -1])
        self.high_action = np.array([1, 1, 1])
        self.action_space = spaces.Box(low=self.low_action, high=self.high_action, dtype=np.float32)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(2,), dtype=np.float32)
        self.environment = zss_kun.Environment(port)
        self.environment.start_all()
        # zss_kun.initBP()
        sleep(0.1)
    def step(self, action=[0,0,0]):
        # sleep(0.1)
        # print("markaction : ",action[0],action[1],action[2])
        # print(zss_kun.np2v(action))
        action = np.float64(action)
        # t = zss_kun.np2v(action)
        # print("markactio  : ",t[0],t[1],t[2])
        feedback = self.environment.step(zss_kun.np2v(action))
        new_obs = feedback.state
        reward = feedback.reward
        done = feedback.done
        return new_obs, reward, done, {}
    def reset(self):
        feedback = self.environment.reset()
        return feedback.state
