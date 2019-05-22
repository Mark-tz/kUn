import rllite
import time
from rllite import SAC
from env import Env
import numpy as np

# from rllite.common import choose_gpu, GymDelay

# choose your GPU if you have more than one
# choose_gpu(0)
env = Env()
# set
model = SAC(
    external_env = env, # import your env
    env_name = "ssl_env", # your env name
    load_dir = './ckpt',
    log_dir = "./log",
    buffer_size = 1e6,
    seed = 1,
    max_episode_steps = 3000, # manual set
    batch_size = 64,
    discount = 0.99,
    learning_starts = 1000,
    tau = 0.005,
    save_eps_num = 100
	)

# model.learn(1e6)

timesteps = 0
total_timesteps = 1e6
max_eps_steps = 500

# train
while timesteps < total_timesteps:
    done = False
    eps_steps = 0
    obs = model.env.reset()
    episode_reward = 0
    while not done and eps_steps < max_eps_steps:
        action = model.predict(obs)
        # action = (action + np.random.normal(0, 0.2, size=env.action_space.shape[0])).clip(env.action_space.low, env.action_space.high)
        new_obs, reward, done, info = model.env.step(action)
        model.replay_buffer.push(obs, action, reward, new_obs, done)
        obs = new_obs
        eps_steps += 1
        timesteps += 1
        episode_reward += reward
        if timesteps > model.learning_starts :
            model.train_step()
    if eps_steps < 5:
        continue
    model.episode_num += 1
    model.writer.add_scalar('episode_reward', episode_reward, model.episode_num)
    if model.episode_num % 100 == 0:
        print("markmarksavesave")
        model.save("./ckpt","ssl_env")