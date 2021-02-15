import numpy as np
import matplotlib.pyplot as plt
from numpy import *
import matplotlib.animation as manimation

grid_data_file = 'data.txt'
x, y = np.genfromtxt(grid_data_file, unpack=True)

plt.rcParams['animation.ffmpeg_path']='C:/Users/d-w-h/Downloads/ffmpeg-20200818-1c7e55d-win64-static/ffmpeg-20200818-1c7e55d-win64-static/bin/ffmpeg.exe'
writer=manimation.FFMpegWriter(bitrate=20000, fps=30)

fig = plt.figure(figsize=(8,8))

track_x = []
track_y = []

def animate(i):
    print(i)
    fig.clear()

    track_x.append(x[i])
    track_y.append(y[i])
    
    ax = plt.axes(xlim=(-15, 15), ylim=(-15, 15))
    cont = plt.scatter(x[i], y[i], s=300, c='blue')
    cont = plt.plot(track_x, track_y)
    return cont

size_t = int(size(x))
anim = manimation.FuncAnimation(fig, animate, frames=size_t, repeat=False)

print("Done Animation, start saving")

anim.save('GRSW_2.mp4', writer=writer, dpi=200)
