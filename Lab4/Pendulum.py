# Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
 
plt.figure(figsize=(25, 50), dpi=80)
fig, axs = plt.subplots(2)
fig.suptitle('Pendolo forzato con RK4 per vari $Delta t$')
 
# Data per x(t) e e(t)
x1, y1, e1 = np.loadtxt('PendoloCaoticodt0.010.dat', usecols=(2, 0, 3), unpack=True)
x2, y2, e2 = np.loadtxt('PendoloCaoticodt0.020.dat', usecols=(2, 0, 3), unpack=True)
x3, y3, e3 = np.loadtxt('PendoloCaoticodt0.030.dat', usecols=(2, 0, 3), unpack=True)
x4, y4, e4 = np.loadtxt('PendoloCaoticodt0.040.dat', usecols=(2, 0, 3), unpack=True)
x5, y5, e5 = np.loadtxt('PendoloCaoticodt0.050.dat', usecols=(2, 0, 3), unpack=True)
axs[0].plot(x1, y1, color='darkslategrey', label='$dt = 0.010$', alpha=0.5, linewidth=0.5)
axs[0].plot(x2, y2, color='blue', label='$dt = 0.020$', alpha=0.5, linewidth=0.5)
axs[0].plot(x3, y3, color='green', label='$dt = 0.030$', alpha=0.5, linewidth=0.5)
axs[0].plot(x4, y4, color='skyblue', label='$dt = 0.040$', alpha=0.5, linewidth=0.5)
axs[0].plot(x5, y5, color='red', label='$dt = 0.050$', alpha=0.5, linewidth=0.5)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(e1, y1, color='darkslategrey', label='$dt = 0.010$', alpha=0.5, linewidth=0.5)
axs[1].plot(e2, y2, color='blue', label='$dt = 0.020$', alpha=0.5, linewidth=0.5)
axs[1].plot(e3, y3, color='green', label='$dt = 0.030$', alpha=0.5, linewidth=0.5)
axs[1].plot(e4, y4, color='skyblue', label='$dt = 0.040$', alpha=0.5, linewidth=0.5)
axs[1].plot(e5, y5, color='red', label='$dt = 0.050$', alpha=0.5, linewidth=0.5)
axs[1].set(xlabel='$t$', ylabel='$E(t)$')
for ax in axs.flat:
	ax.legend()
	ax.ticklabel_format(useOffset=False)
	ax.legend(loc='upper left')
plt.savefig('PendoloForzato.pdf')
