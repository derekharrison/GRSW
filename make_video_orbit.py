import numpy as np
import matplotlib.pyplot as plt
from numpy import *
import matplotlib.animation as manimation

grid_data_file = 'data.txt'
x, y, t = np.genfromtxt(grid_data_file, unpack=True)

size_vec = size(x)
min_t = t[0]
max_t = t[size_vec - 1]
dt = (max_t - min_t) / (0.25 * size_vec)

t_r = np.arange(min_t, max_t, dt).tolist()
print("size vec")
print(size_vec)
x_r = np.interp(t_r, t, x)
y_r = np.interp(t_r, t, y)

plt.rcParams['animation.ffmpeg_path']='C:/Users/d-w-h/Downloads/ffmpeg-20200818-1c7e55d-win64-static/ffmpeg-20200818-1c7e55d-win64-static/bin/ffmpeg.exe'
writer=manimation.FFMpegWriter(bitrate=20000, fps=30)

fig = plt.figure(figsize=(8,8))

track_x = []
track_y = []

def animate(i):
    print(i)
    fig.clear()

    track_x.append(x_r[i])
    track_y.append(y_r[i])
    
    ax = plt.axes(xlim=(-15, 15), ylim=(-15, 15))
    cont = plt.scatter(x_r[i], y_r[i], s=300, c='blue')
    cont = plt.plot(track_x, track_y)
    return cont

size_t = 2000
anim = manimation.FuncAnimation(fig, animate, frames=size_t, repeat=False)

print("Done Animation, start saving")

anim.save('GRSW_2.mp4', writer=writer, dpi=200)
