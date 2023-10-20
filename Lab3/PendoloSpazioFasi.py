# Importing libraries 
import matplotlib.pyplot as plt 
import numpy as np 

from scipy.optimize import curve_fit

plt.figure(figsize=(15, 26), dpi=80)
fig, axs = plt.subplots(2)
fig.suptitle('Spazio delle fasi di Pendolo semplice con Eulero-Cromer per vari $\Delta t$')

# Data per spazio delle fasi
x_1, y_1 = np.loadtxt('Pendolo0.001.dat', usecols=(0, 1), unpack=True)
x_2, y_2 = np.loadtxt('Pendolo0.002.dat', usecols=(0, 1), unpack=True)
x_3, y_3 = np.loadtxt('Pendolo0.003.dat', usecols=(0, 1), unpack=True)
x_4, y_4 = np.loadtxt('Pendolo0.004.dat', usecols=(0, 1), unpack=True)
a_1, b_1 = np.loadtxt('Pendolo0.001.dat', usecols=(0, 3), unpack=True)
a_2, b_2 = np.loadtxt('Pendolo0.002.dat', usecols=(0, 3), unpack=True)
a_3, b_3 = np.loadtxt('Pendolo0.003.dat', usecols=(0, 3), unpack=True)
a_4, b_4 = np.loadtxt('Pendolo0.004.dat', usecols=(0, 3), unpack=True)

axs[0].plot(x_1, y_1, color='darkslategrey', label='$\Delta t = 0.001 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[0].plot(x_2, y_2, color='blue', label='$\Delta t = 0.002 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[0].plot(x_3, y_3, color='cyan', label='$\Delta t = 0.003 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[0].plot(x_4, y_4, color='skyblue', label='$\Delta t = 0.004 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[0].set(xlabel='$x(t)$', ylabel='$v(t)$')
axs[1].plot(a_1, b_1, color='darkslategrey', label='$\Delta t = 0.001 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[1].plot(a_2, b_2, color='blue', label='$\Delta t = 0.002 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[1].plot(a_3, b_3, color='cyan', label='$\Delta t = 0.003 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[1].plot(a_4, b_4, color='skyblue', label='$\Delta t = 0.004 \ s$', alpha=0.5, linestyle='dashed', linewidth=0.7)
axs[1].set(xlabel='$x(t)$', ylabel='$E(t)$')

for ax in axs.flat:
    ax.legend()
    ax.ticklabel_format(useOffset=False)
axs[0].legend(loc='upper right')
plt.savefig('SpazioFasi_Pendolo.pdf')
plt.show()