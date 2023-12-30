import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(3,2)
fig.set_figwidth(20)
fig.set_figheight(20)
fig.suptitle('Random Walk for various number of steps', fontsize=20)

x_holder = {}
y_holder = {}
N_holder = {}
meanx_holder = {}
meany_holder = {}
stdx_holder = {}
stdy_holder = {}
n = 10

for i in range(1, 7):
    #Data
    x_holder['x' + str(i)], y_holder['y' + str(i)] = np.loadtxt(f'/workspaces/Computazionale2/RandomWalk/File/RW2Dn={n}.dat', usecols=(0, 1), unpack=True)
    N_holder['N' + str(i)] = len(x_holder['x' + str(i)])
    meanx_holder['meanx' + str(i)], meany_holder['meany' + str(i)] = np.loadtxt(f"/workspaces/Computazionale2/RandomWalk/File/MuStdn={n}.dat", usecols=(0, 1), unpack=True)
    stdx_holder['stdx' + str(i)], stdy_holder['stdy' + str(i)] = np.loadtxt(f"/workspaces/Computazionale2/RandomWalk/File/MuStdn={n}.dat", usecols=(2, 3), unpack=True)
    n += 5*n

locals().update(x_holder)
locals().update(y_holder)
locals().update(N_holder)
locals().update(meanx_holder)
locals().update(meany_holder)
locals().update(stdx_holder)
locals().update(stdy_holder)
#Vari plot
f1 = ax[0,0].plot(x1, y1, color='skyblue', label=f'Random Walk {N1-1:.0f} steps',  zorder=-1)
f2 = ax[0,1].plot(x2, y2, color='skyblue', label=f'Random Walk {N2-1:.0f} steps',  zorder=-1)
f3 = ax[1,0].plot(x3, y3, color='skyblue', label=f'Random Walk {N3-1:.0f} steps',  zorder=-1)
f4 = ax[1,1].plot(x4, y4, color='skyblue', label=f'Random Walk {N4-1:.0f} steps',  zorder=-1)
f5 = ax[2,0].plot(x5, y5, color='skyblue', label=f'Random Walk {N5-1:.0f} steps',  zorder=-1)
f6 = ax[2,1].plot(x6, y6, color='skyblue', label=f'Random Walk {N6-1:.0f} steps',  zorder=-1)
#Initial Points plots
ax[0,0].scatter(x1[0], y1[0], color='red', label=f'Starting Point: ({x1[0]:.0f}, {y1[0]:.0f})',  zorder=1)
ax[0,1].scatter(x2[0], y2[0], color='red', label=f'Starting Point: ({x2[0]:.0f}, {y2[0]:.0f})',  zorder=1)
ax[1,0].scatter(x3[0], y3[0], color='red', label=f'Starting Point: ({x3[0]:.0f}, {y3[0]:.0f})',  zorder=1)
ax[1,1].scatter(x4[0], y4[0], color='red', label=f'Starting Point: ({x4[0]:.0f}, {y4[0]:.0f})',  zorder=1)
ax[2,0].scatter(x5[0], y5[0], color='red', label=f'Starting Point: ({x5[0]:.0f}, {y5[0]:.0f})',  zorder=1)
ax[2,1].scatter(x6[0], y6[0], color='red', label=f'Starting Point: ({x6[0]:.0f}, {y6[0]:.0f})',  zorder=1)
#Final Points plots
ax[0,0].scatter(x1[-1], y1[-1], color='darkslategrey', label=f'Final Point:  ({x1[-1]:.0f}, {y1[-1]:.0f})', zorder=1)
ax[0,1].scatter(x2[-1], y2[-1], color='darkslategrey', label=f'Final Point:  ({x2[-1]:.0f}, {y2[-1]:.0f})', zorder=1)
ax[1,0].scatter(x3[-1], y3[-1], color='darkslategrey', label=f'Final Point:  ({x3[-1]:.0f}, {y3[-1]:.0f})', zorder=1)
ax[1,1].scatter(x4[-1], y4[-1], color='darkslategrey', label=f'Final Point:  ({x4[-1]:.0f}, {y4[-1]:.0f})', zorder=1)
ax[2,0].scatter(x5[-1], y5[-1], color='darkslategrey', label=f'Final Point:  ({x5[-1]:.0f}, {y5[-1]:.0f})', zorder=1)
ax[2,1].scatter(x6[-1], y6[-1], color='darkslategrey', label=f'Final Point:  ({x6[-1]:.0f}, {y6[-1]:.0f})', zorder=1)
#Empty plots
ax[0,0].plot([], [], '', label=f'Mean (x,y): ({meanx1:.2f}, {meany1:.2f})', alpha=0)
ax[0,0].plot([], [], '', label=f'Std (x,y): ({stdx1:.2f}, {stdy1:.2f})', alpha=0)

ax[0,1].plot([], [], '', label=f'Mean (x,y): ({meanx2:.2f}, {meany2:.2f})', alpha=0)
ax[0,1].plot([], [], '', label=f'Std (x,y): ({stdx2:.2f}, {stdy2:.2f})', alpha=0)

ax[1,0].plot([], [], '', label=f'Mean (x,y): ({meanx3:.2f}, {meany3:.2f})', alpha=0)
ax[1,0].plot([], [], '', label=f'Std (x,y): ({stdx3:.2f}, {stdy3:.2f})', alpha=0)

ax[1,1].plot([], [], '', label=f'Mean (x,y): ({meanx4:.2f}, {meany4:.2f})', alpha=0)
ax[1,1].plot([], [], '', label=f'Std (x,y): ({stdx4:.2f}, {stdy4:.2f})', alpha=0)

ax[2,0].plot([], [], '', label=f'Mean (x,y): ({meanx5:.2f}, {meany5:.2f})', alpha=0)
ax[2,0].plot([], [], '', label=f'Std (x,y): ({stdx5:.2f}, {stdy5:.2f})', alpha=0)

ax[2,1].plot([], [], '', label=f'Mean (x,y): ({meanx6:.2f}, {meany6:.2f})', alpha=0)
ax[2,1].plot([], [], '', label=f'Std (x,y): ({stdx6:.2f}, {stdy6:.2f})', alpha=0)
for ax in ax.flat:
    ax.legend(fontsize=10)
    ax.set(xlabel='x', ylabel='y')
plt.savefig("RandomWalk2D.png")
plt.show()
