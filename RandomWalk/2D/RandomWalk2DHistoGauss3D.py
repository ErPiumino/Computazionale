import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm
from   scipy.stats import multivariate_normal

# creating a figure with 2 axes
fig, ax = plt.subplots(nrows=2, ncols=3, subplot_kw=dict(projection="3d"))
fig.set_figwidth(16)
fig.set_figheight(11)
plt.subplots_adjust(wspace=0.1,hspace=0.2)
labels_x, labels_y, labels_z = [['x data']*3]*2, [['y data']*3]*2, [['Frequency']*3]*2
for i in range(len(ax)):
    for j in range(len(ax[i])):
        ax[i,j].set_xlabel(labels_x[i][j])
        ax[i,j].set_ylabel(labels_y[i][j])
        ax[i,j].set_zlabel(labels_z[i][j])

# generating 2d data
fig.suptitle('3d Histograms of final position of 1000 Random Walk for various number of steps', fontsize=20)
x1, y1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=10.dat', usecols=(0, 1), unpack=True)
x2, y2 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=60.dat', usecols=(0, 1), unpack=True)
x3, y3 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=360.dat', usecols=(0, 1), unpack=True)
x4, y4 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=2160.dat', usecols=(0, 1), unpack=True)
x5, y5 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=12960.dat', usecols=(0, 1), unpack=True)
x6, y6 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW2DHiston=77760.dat', usecols=(0, 1), unpack=True)

h1, xbins1, ybins1 = np.histogram2d(x1,y1, bins=[5, 5])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[0,0].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='10 steps')


h1, xbins1, ybins1 = np.histogram2d(x2,y2, bins=[10, 10])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[0,1].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='60 steps')

h1, xbins1, ybins1 = np.histogram2d(x3,y3, bins=[15, 15])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[0,2].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='360 steps')

h1, xbins1, ybins1 = np.histogram2d(x4,y4, bins=[15, 15])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[1,0].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='2160 steps')

h1, xbins1, ybins1 = np.histogram2d(x5,y5, bins=[20, 20])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[1,1].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='12960 steps')

h1, xbins1, ybins1 = np.histogram2d(x6,y6, bins=[20, 20])
_xx, _yy = np.meshgrid(xbins1[:-1], ybins1[:-1])
bottom = np.zeros_like(_xx)
top = h1
width = xbins1[1]-xbins1[0]
depth = ybins1[1]-ybins1[0]
ax[1,2].bar3d(_xx.flatten(), _yy.flatten(), bottom.flatten(), width, depth, h1.flatten(), shade=True, label='77760 steps')

for ax in ax.flat:
    ax.legend()

plt.savefig("Istogrammi3d.png")