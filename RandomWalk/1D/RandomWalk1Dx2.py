import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(3,2)
fig.set_figwidth(20)
fig.set_figheight(20)
fig.suptitle('Random Walk for various number of steps', fontsize=20)
x1, t1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=10.dat', usecols=(0, 1), unpack=True)
x2, t2 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=60.dat', usecols=(0, 1), unpack=True)
x3, t3 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=360.dat', usecols=(0, 1), unpack=True)
x4, t4 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=2160.dat', usecols=(0, 1), unpack=True)
x5, t5 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=12960.dat', usecols=(0, 1), unpack=True)
x6, t6 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=77760.dat', usecols=(0, 1), unpack=True)
#Vari plot
ax[0,0].loglog(t1, x1**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[0,0].plot(np.linspace(0, np.max(t1)), np.linspace(0, np.max(t1)), color='grey',  zorder=-1, linestyle='--')
ax[0,1].loglog(t2, x2**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[0,1].plot(np.linspace(0, np.max(t2)), np.linspace(0, np.max(t2)), color='grey',  zorder=-1, linestyle='--')
ax[1,0].loglog(t3, x3**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[1,0].plot(np.linspace(0, np.max(t3)), np.linspace(0, np.max(t3)), color='grey',  zorder=-1, linestyle='--')
ax[1,1].loglog(t4, x4**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[1,1].plot(np.linspace(0, np.max(t4)), np.linspace(0, np.max(t4)), color='grey',  zorder=-1, linestyle='--')
ax[2,0].loglog(t5, x5**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[2,0].plot(np.linspace(0, np.max(t5)), np.linspace(0, np.max(t5)), color='grey',  zorder=-1, linestyle='--')
ax[2,1].loglog(t6, x6**2, color='skyblue', label='$x(t)^2$',  zorder=-1)
ax[2,1].plot(np.linspace(0, np.max(t6)), np.linspace(0, np.max(t6)), color='grey',  zorder=-1, linestyle='--')
#Writing sets
ax[0,0].plot([], [], '', label='Steps=10', alpha=0)
ax[0,1].plot([], [], '', label='Steps=60', alpha=0)
ax[1,0].plot([], [], '', label='Steps=360', alpha=0)
ax[1,1].plot([], [], '', label='Steps=2160', alpha=0)
ax[2,0].plot([], [], '', label='Steps=12960', alpha=0)
ax[2,1].plot([], [], '', label='Steps=77760', alpha=0)
for ax in ax.flat:
    ax.legend(fontsize=10)
    ax.set(xlabel='t', ylabel='$x(t)^2$')
plt.savefig("RandomWalk1Dx2.png")