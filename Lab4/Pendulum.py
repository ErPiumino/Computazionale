# Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
 
#plt.figure(figsize=(25, 50), dpi=80)
fig, axs = plt.subplots(2)
fig.suptitle('Pendolo forzato con RK4 per vari $f0$')
 
# Data per x(t) e e(t)
x1, y1, v1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaoticoF00.900.dat', usecols=(2, 0, 1), unpack=True)
x2, y2, v2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaoticoF01.070.dat', usecols=(2, 0, 1), unpack=True)
x3, y3, v3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaoticoF01.150.dat', usecols=(2, 0, 1), unpack=True)
x4, y4, v4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaoticoF01.470.dat', usecols=(2, 0, 1), unpack=True)
x5, y5, v5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloCaoticoF01.500.dat', usecols=(2, 0, 1), unpack=True)
axs[0].plot(x1, y1, color='darkslategrey', label='$F0 = 0.900$', alpha=0.5, linewidth=0.5)
axs[0].plot(x2, y2, color='blue', label='$F0 = 1.070$', alpha=0.5, linewidth=0.5)
axs[0].plot(x3, y3, color='green', label='$F0 = 1.150$', alpha=0.5, linewidth=0.5)
axs[0].plot(x4, y4, color='skyblue', label='$F0 = 1.470$', alpha=0.5, linewidth=0.5)
axs[0].plot(x5, y5, color='red', label='$F0 = 1.500$', alpha=0.5, linewidth=0.5)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(y1, v1, color='darkslategrey', alpha=0.5, linewidth=0.5)
axs[1].plot(y2, v2, color='blue', alpha=0.5, linewidth=0.5)
axs[1].plot(y3, v3, color='green', alpha=0.5, linewidth=0.5)
axs[1].plot(y4, v4, color='skyblue', alpha=0.5, linewidth=0.5)
axs[1].plot(y5, v5, color='red', alpha=0.5, linewidth=0.5)
axs[1].set(xlabel='$x(t)$', ylabel='$v(t)$')
handles, labels = axs[-1].get_legend_handles_labels()
for ax in axs[:-1]:
	h, l=ax.get_legend_handles_labels()
	handles += h
	labels += l
fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(1, 0.75))
fig.subplots_adjust(right=0.7)
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/PendoloForzato.pdf')
