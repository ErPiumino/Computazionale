# Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
 
#plt.figure(figsize=(25, 50), dpi=80)
fig, axs = plt.subplots(3,2)
fig.set_figwidth(15)
fig.set_figheight(15)
fig.suptitle('Sezioni di Poincare per varie $f0$')
 
# Data per x(t) e e(t)
x1, v1 = np.loadtxt('PendoloPoincareF00.900.dat', usecols=(0, 1), unpack=True)
x2, v2 = np.loadtxt('PendoloPoincareF01.070.dat', usecols=(0, 1), unpack=True)
x3, v3 = np.loadtxt('PendoloPoincareF01.150.dat', usecols=(0, 1), unpack=True)
x4, v4 = np.loadtxt('PendoloPoincareF01.470.dat', usecols=(0, 1), unpack=True)
x5, v5 = np.loadtxt('PendoloPoincareF01.500.dat', usecols=(0, 1), unpack=True)
axs[0,0].scatter(x1, v1, color='darkslategrey', label='$F0 = 0.900$', marker='.', s=0.001)
axs[0,0].legend(loc='upper left', fontsize=8)
axs[0,1].scatter(x2, v2, color='blue', label='$F0 = 1.07$', s=0.0000001)
axs[0,1].legend(loc='upper left', fontsize=8)
axs[1,0].scatter(x3, v3, color='green', label='$F0 = 1.15$', s=0.0000001)
axs[1,0].legend(loc='upper left', fontsize=8)
axs[1,1].scatter(x4, v4, color='skyblue', label='$F0 = 1.47$', s=0.0000001)
axs[1,1].legend(loc='upper left', fontsize=8)
axs[2,0].scatter(x5, v5, color='red', label='$F0 = 1.50$', s=0.0000001)
axs[2,0].legend(loc='upper left', fontsize=8)
axs[2,1].set_visible(False)
for ax in axs.flat:
	ax.set(xlabel='x(t)', ylabel='v(t)')
fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
plt.savefig('Poincare.pdf')
