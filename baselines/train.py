import gym
import numpy as np
import os
from stable_baselines.sac.policies import MlpPolicy
from stable_baselines.common.vec_env import DummyVecEnv
from stable_baselines import SAC
from env import Env
env = Env()
env = DummyVecEnv([lambda: env])

log_dir = "log/sac_ssl"
os.makedirs(log_dir, exist_ok=True)


model = SAC(MlpPolicy, env, verbose=1,tensorboard_log=log_dir)
model.learn(total_timesteps=10000000, log_interval=10)
model.save("sac_ssl")

del model # remove to demonstrate saving and loading

model = SAC.load("sac_ssl")

obs = env.reset()
while True:
    action, _states = model.predict(obs)
    obs, rewards, dones, info = env.step(action)
    env.render()