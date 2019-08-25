import rllite
import time
from rllite import SAC
from env import Env
import numpy as np
# import pdb
# pdb.set_trace()
# from rllite.common import choose_gpu, GymDelay

# choose your GPU if you have more than one
# choose_gpu(0)
env = Env(10666)
# set
model = SAC(
    external_env = env, # import your env
    env_name = "ssl_env", # your env name
    load_dir = './ckpt',
    log_dir = "./log",
    buffer_size = 1e6,
    seed = 2,
    max_episode_steps = 500, # manual set
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

# tricky limit
xy_acc = 4.0/75.0/2
w_acc = 15.0/75.0
def limitRange(action,minv,maxv):
    if action > maxv:
        return maxv
    elif action < minv:
        return minv
    return action

# train
while timesteps < total_timesteps:
    done = False
    eps_steps = 0
    obs = model.env.reset()
    episode_reward = 0
    old_action = [0.0,0.0,0.0]
    while not done and eps_steps < max_eps_steps:
        action = model.predict(obs)
        action[0] = limitRange(action[0],old_action[0]-xy_acc,old_action[0]+xy_acc)
        action[1] = limitRange(action[1],old_action[1]-xy_acc,old_action[1]+xy_acc)
        action[2] = limitRange(action[2],old_action[2]-w_acc,old_action[2]+w_acc)
        old_action = action
        # action = (action + np.random.normal(0, 0.2, size=env.action_space.shape[0])).clip(env.action_space.low, env.action_space.high)
        new_obs, reward, done, info = model.env.step(action)
        # print("markobs : ",new_obs[0],new_obs[1]);
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