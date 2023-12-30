import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots(3,2)
fig.set_figwidth(20)
fig.set_figheight(20)
fig.suptitle('Random Walk for various number of steps', fontsize=20)
x=np.linspace(0, 77760)
t=np.linspace(0, 77760)
x1, t1 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=10.dat', usecols=(0, 1), unpack=True)
x2, t2 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=60.dat', usecols=(0, 1), unpack=True)
x3, t3 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=360.dat', usecols=(0, 1), unpack=True)
x4, t4 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=2160.dat', usecols=(0, 1), unpack=True)
x5, t5 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=12960.dat', usecols=(0, 1), unpack=True)
x6, t6 = np.loadtxt('/workspaces/Computazionale2/Lab5/File/RW1Dn=77760.dat', usecols=(0, 1), unpack=True)
N1 = len(x1)
N2 = len(x2)
N3 = len(x3)
N4 = len(x4)
N5 = len(x5)
N6 = len(x6)
meanx1, stdx1 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=10.dat", usecols=(0, 1), unpack=True)
meanx2, stdx2 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=60.dat", usecols=(0, 1), unpack=True)
meanx3, stdx3 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=360.dat", usecols=(0, 1), unpack=True)
meanx4, stdx4 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=2160.dat", usecols=(0, 1), unpack=True)
meanx5, stdx5 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=12960.dat", usecols=(0, 1), unpack=True)
meanx6, stdx6 = np.loadtxt("/workspaces/Computazionale2/Lab5/File/1DMuStdn=77760.dat", usecols=(0, 1), unpack=True)
#Vari plot
f1 = ax[0,0].plot(t1, x1, color='skyblue', label=f'Random Walk {N1-1:.0f} steps',  zorder=-1)
f2 = ax[0,1].plot(t2, x2, color='skyblue', label=f'Random Walk {N2-1:.0f} steps',  zorder=-1)
f3 = ax[1,0].plot(t3, x3, color='skyblue', label=f'Random Walk {N3-1:.0f} steps',  zorder=-1)
f4 = ax[1,1].plot(t4, x4, color='skyblue', label=f'Random Walk {N4-1:.0f} steps',  zorder=-1)
f5 = ax[2,0].plot(t5, x5, color='skyblue', label=f'Random Walk {N5-1:.0f} steps',  zorder=-1)
f6 = ax[2,1].plot(t6, x6, color='skyblue', label=f'Random Walk {N6-1:.0f} steps',  zorder=-1)
#Initial Points plots
ax[0,0].scatter(t1[0], x1[0], color='red', label=f'Starting Point: ({x1[0]:.0f})',  zorder=1)
ax[0,1].scatter(t2[0], x2[0], color='red', label=f'Starting Point: ({x2[0]:.0f})',  zorder=1)
ax[1,0].scatter(t3[0], x3[0], color='red', label=f'Starting Point: ({x3[0]:.0f})',  zorder=1)
ax[1,1].scatter(t4[0], x4[0], color='red', label=f'Starting Point: ({x4[0]:.0f})',  zorder=1)
ax[2,0].scatter(t5[0], x5[0], color='red', label=f'Starting Point: ({x5[0]:.0f})',  zorder=1)
ax[2,1].scatter(t6[0], x6[0], color='red', label=f'Starting Point: ({x6[0]:.0f})',  zorder=1)
#Final Points plots
ax[0,0].scatter(t1[-1], x1[-1], color='blue', label=f'Final Point: ({x1[-1]:.0f})',  zorder=1)
ax[0,1].scatter(t2[-1], x2[-1], color='blue', label=f'Final Point: ({x2[-1]:.0f})',  zorder=1)
ax[1,0].scatter(t3[-1], x3[-1], color='blue', label=f'Final Point: ({x3[-1]:.0f})',  zorder=1)
ax[1,1].scatter(t4[-1], x4[-1], color='blue', label=f'Final Point: ({x4[-1]:.0f})',  zorder=1)
ax[2,0].scatter(t5[-1], x5[-1], color='blue', label=f'Final Point: ({x5[-1]:.0f})',  zorder=1)
ax[2,1].scatter(t6[-1], x6[-1], color='blue', label=f'Final Point: ({x6[-1]:.0f})',  zorder=1)
#Empty plots
ax[0,0].plot([], [], '', label=f'Mean (x) =  ({meanx1:.2f} $\pm$ {stdx1:.2f})', alpha=0)
ax[0,1].plot([], [], '', label=f'Mean (x) =  ({meanx2:.2f} $\pm$ {stdx2:.2f})', alpha=0)
ax[1,0].plot([], [], '', label=f'Mean (x) =  ({meanx3:.2f} $\pm$ {stdx3:.2f})', alpha=0)
ax[1,1].plot([], [], '', label=f'Mean (x) =  ({meanx4:.2f} $\pm$ {stdx4:.2f})', alpha=0)
ax[2,0].plot([], [], '', label=f'Mean (x) =  ({meanx5:.2f} $\pm$ {stdx5:.2f})', alpha=0)
ax[2,1].plot([], [], '', label=f'Mean (x) =  ({meanx6:.2f} $\pm$ {stdx6:.2f})', alpha=0)
for ax in ax.flat:
    ax.legend(fontsize=10)
    ax.set(xlabel='t', ylabel='x(t)')
plt.savefig("RandomWalk1D.png")
