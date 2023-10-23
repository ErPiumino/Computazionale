# Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
 
plt.figure(figsize=(12, 26), dpi=80)
fig, axs = plt.subplots(2)
fig.suptitle('Pendolo smorzato con Eulero-Cromer per vari $Delta t$')
 
# Data per x(t) e e(t)
x1, y1, e1 = np.loadtxt('PendoloCaoticoF00.900.dat', usecols=(2, 0, 3), unpack=True)
x2, y2, e2 = np.loadtxt('PendoloCaoticoF01.070.dat', usecols=(2, 0, 3), unpack=True)
x3, y3, e3 = np.loadtxt('PendoloCaoticoF01.150.dat', usecols=(2, 0, 3), unpack=True)
x4, y4, e4 = np.loadtxt('PendoloCaoticoF01.470.dat', usecols=(2, 0, 3), unpack=True)
x5, y5, e5 = np.loadtxt('PendoloCaoticoF01.500.dat', usecols=(2, 0, 3), unpack=True)
axs[0].plot(x1, y1, color='darkslategrey', label='$F0 = 0.900$', alpha=0.5)
axs[0].plot(x2, y2, color='blue', label='$F0 = 1.070$', alpha=0.5)
axs[0].plot(x3, y3, color='cyan', label='$F0 = 1.150$', alpha=0.5)
axs[0].plot(x4, y4, color='skyblue', label='$F0 = 1.470$', alpha=0.5)
axs[0].plot(x5, y5, color='grey', label='$F0 = 1.500$', alpha=0.5)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(e1, y1, color='darkslategrey', label='$F0 = 0.900$', alpha=0.5)
axs[1].plot(e2, y2, color='blue', label='$F0 = 1.070$', alpha=0.5)
axs[1].plot(e3, y3, color='cyan', label='$F0 = 1.150$', alpha=0.5)
axs[1].plot(e4, y4, color='skyblue', label='$F0 = 1.470$', alpha=0.5)
axs[1].plot(e5, y5, color='grey', label='$F0 = 1.500$', alpha=0.5)
axs[1].set(xlabel='$t$', ylabel='$E(t)$')
for ax in axs.flat:
	ax.legend()
	ax.ticklabel_format(useOffset=False)
axs[0].legend(loc='upper right')
plt.savefig('PendoloForzato.pdf')
