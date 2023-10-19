# Importing libraries 
import matplotlib.pyplot as plt 
import numpy as np 
  
plt.figure(figsize=(12, 26), dpi=80)
fig, axs = plt.subplots(3)
fig.suptitle('Pendolo smorzato con Eulero-Cromer per vari $\Delta t$')

# Data per x(t)
x1, y1 = np.loadtxt('PendoloSmorzato0.01.dat', usecols=(2, 0), unpack=True)
x2, y2 = np.loadtxt('PendoloSmorzato0.02.dat', usecols=(2, 0), unpack=True)
x3, y3 = np.loadtxt('PendoloSmorzato0.03.dat', usecols=(2, 0), unpack=True)
x4, y4 = np.loadtxt('PendoloSmorzato0.04.dat', usecols=(2, 0), unpack=True)

# Data per E(t)
e1, te1 = np.loadtxt('PendoloSmorzato0.01.dat', usecols=(2, 3), unpack=True)
e2, te2 = np.loadtxt('PendoloSmorzato0.02.dat', usecols=(2, 3), unpack=True)
e3, te3 = np.loadtxt('PendoloSmorzato0.03.dat', usecols=(2, 3), unpack=True)
e4, te4 = np.loadtxt('PendoloSmorzato0.04.dat', usecols=(2, 3), unpack=True)

# Data per spazio delle fasi
x_1, y_1 = np.loadtxt('PendoloSmorzato0.01.dat', usecols=(1, 0), unpack=True)
x_2, y_2 = np.loadtxt('PendoloSmorzato0.02.dat', usecols=(1, 0), unpack=True)
x_3, y_3 = np.loadtxt('PendoloSmorzato0.03.dat', usecols=(1, 0), unpack=True)
x_4, y_4 = np.loadtxt('PendoloSmorzato0.04.dat', usecols=(1, 0), unpack=True)

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
axs[2].plot(x_1, y_1, color='darkslategrey', label='$\Delta t = 0.001 \ s$', alpha=0.5, linestyle='dashed')
axs[2].plot(x_2, y_2, color='blue', label='$\Delta t = 0.002 \ s$', alpha=0.5, linestyle='dashed')
axs[2].plot(x_3, y_3, color='cyan', label='$\Delta t = 0.003 \ s$', alpha=0.5, linestyle='dashed')
axs[2].plot(x_4, y_4, color='skyblue', label='$\Delta t = 0.004 \ s$', alpha=0.5, linestyle='dashed')
axs[2].set(xlabel='$v(t)$', ylabel='$x(t)$')
for ax in axs.flat:
    ax.legend()
    ax.ticklabel_format(useOffset=False)
axs[0].legend(loc='upper right')
plt.savefig('PendoloSmorzato.pdf')
plt.show() 