import numpy as np
import matplotlib.pyplot as plt
from numpy import *
import matplotlib.animation as manimation

grid_data_file = 'data.txt'
x, y, t = np.genfromtxt(grid_data_file, unpack=True)

plt.plot(x, y)
plt.show()
