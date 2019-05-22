import gym
from gym import spaces
from gym.utils import seeding
import numpy as np
from time import sleep
from array import array
import zss_env
import sys
class Env(gym.Env):
    def __init__(self):
        self.low_action = np.array([-1, -1])
        self.high_action = np.array([1, 1])
        self.action_space = spaces.Box(low=self.low_action, high=self.high_action, dtype=np.float32)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(2,), dtype=np.float32)
        self.environment = zss_env.Environment(10666)
        self.environment.start_all()
        sleep(0.3)
    def step(self, action=[0,0]):
        sleep(0.007)
        feedback = self.environment.step(array('d',[action[0],action[1]]),action.size)
        new_obs = feedback.state
        reward = feedback.reward
        done = feedback.done
        return new_obs, reward, done, {}
    def reset(self):
        feedback = self.environment.reset()
        return feedback.state
