import seaborn as sns
import numpy as np
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from scipy.stats import multivariate_normal

x, y, z = np.loadtxt("/workspaces/Computazionale2/RandomWalk/File/RW2DPt=100000.dat", unpack=True)
fig = plt.figure ( figsize=(10, 6) )
ax = Axes3D ( fig, auto_add_to_figure=False )
fig.add_axes ( ax )
ax.scatter (x, y, z, s = 40, marker = 'o', alpha = 1, label = '')
ax.set_xlabel ( 'th' )
ax.set_ylabel ( 'pdvalue' )
ax.set_zlabel ( 'my_val' )
plt.savefig("RandomWalk2DP.png")
