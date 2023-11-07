import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

ax = plt.figure().add_subplot(projection='3d')

# Plot a sin curve using the x and y axes.
x, y, z = np.loadtxt('/workspaces/Computazionale/Esonero/File/Parte0dt0.01.dat', usecols=(2, 1, 0), unpack=True)
ax.scatter(x, y, z, c = plt.cm.jet(z/(0.5*max(z))), label='(x(t), y(t))', s=0.5) 

# Make legend, set axes limits and labels
ax.legend()
ax.set_xlabel('x(t)')
ax.set_ylabel('y(t)')
ax.set_zlabel('t[s]')
ax.set_zlim(0, 15)

# Customize the view angle so it's easier to see that the scatter points lie
# on the plane y=0
ax.view_init(elev=25., azim=-35, roll=0)

plt.savefig("Parte03d.pdf")