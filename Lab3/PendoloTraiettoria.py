# Importing libraries 
import matplotlib.pyplot as plt 
import numpy as np 
  
fig, axs = plt.subplots(2)
fig.suptitle('Pendolo semplice con Eulero-Cromer per vari $\Delta t$')

# Data per x(t)
x1, y1 = np.loadtxt('Pendolo0.001.dat', usecols=(2, 0), unpack=True)
x2, y2 = np.loadtxt('Pendolo0.002.dat', usecols=(2, 0), unpack=True)
x3, y3 = np.loadtxt('Pendolo0.003.dat', usecols=(2, 0), unpack=True)
x4, y4 = np.loadtxt('Pendolo0.004.dat', usecols=(2, 0), unpack=True)

# Data per E(t)
e1, te1 = np.loadtxt('Pendolo0.001.dat', usecols=(2, 3), unpack=True)
e2, te2 = np.loadtxt('Pendolo0.002.dat', usecols=(2, 3), unpack=True)
e3, te3 = np.loadtxt('Pendolo0.003.dat', usecols=(2, 3), unpack=True)
e4, te4 = np.loadtxt('Pendolo0.004.dat', usecols=(2, 3), unpack=True)

axs[0].plot(x1, y1, color='darkslategrey', label='$\Delta t = 0.001 \ s$', alpha=0.5)
axs[0].plot(x2, y2, color='blue', label='$\Delta t = 0.002 \ s$', alpha=0.5)
axs[0].plot(x3, y3, color='cyan', label='$\Delta t = 0.003 \ s$', alpha=0.5)
axs[0].plot(x4, y4, color='skyblue', label='$\Delta t = 0.004 \ s$', alpha=0.5)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(e1, te1, color='darkslategrey', label='$\Delta t = 0.001 \ s$', alpha=0.5)
axs[1].plot(e2, te2, color='blue', label='$\Delta t = 0.002 \ s$', alpha=0.5)
axs[1].plot(e3, te3, color='cyan', label='$\Delta t = 0.003 \ s$', alpha=0.5)
axs[1].plot(e4, te4, color='skyblue', label='$\Delta t = 0.004 \ s$', alpha=0.5)
axs[1].set(xlabel='$t$', ylabel='$E(t)$')
for ax in axs.flat:
    ax.legend()
    ax.ticklabel_format(useOffset=False)
axs[0].legend(loc='upper right')
plt.tight_layout() 
plt.savefig('Pendolo.pdf')
plt.show() 