# Importing libraries 
import matplotlib.pyplot as plt 
import numpy as np 

fig, axs = plt.subplots(2)
fig.suptitle('Confronto tra Metodi per $t=100 s$')
x1, y1 = np.loadtxt('E100.dat', usecols=(2, 0), unpack=True)
xe1, ye1 = np.loadtxt('E100.dat', usecols=(2, 3), unpack=True)
x2, y2 = np.loadtxt('EC100.dat', usecols=(2, 0), unpack=True)
xe2, ye2 = np.loadtxt('EC100.dat', usecols=(2, 3), unpack=True)
x3, y3 = np.loadtxt('MP100.dat', usecols=(2, 0), unpack=True)
xe3, ye3 = np.loadtxt('MP100.dat', usecols=(2, 3), unpack=True)
x4, y4 = np.loadtxt('MPI100.dat', usecols=(2, 0), unpack=True)
xe4, ye4 = np.loadtxt('MPI100.dat', usecols=(2, 3), unpack=True)
axs[0].plot(x1, y1, color='darkslategrey', label='Eulero', alpha=0.3)
axs[0].plot(x2, y2, color='skyblue', label='Eulero-Cromer', alpha=0.3)
axs[0].plot(x3, y3, color='blue', label='MidPoint', alpha=0.3)
axs[0].plot(x4, y4, color='cyan', label='MidPoint Implicito', alpha=0.3)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(xe1, ye1, color='darkslategrey', label='Eulero', alpha=0.3)
axs[1].plot(xe2, ye2, color='skyblue', label='Eulero-Cromer', alpha=0.3)
axs[1].plot(xe3, ye3, color='blue', label='MidPoint', alpha=0.3)
axs[1].plot(xe4, ye4, color='cyan', label='MidPoint Implicito', alpha=0.3)
axs[1].set(xlabel='$t$', ylabel='$E(t)$')
axs[1].legend()
plt.tight_layout() 
plt.savefig('Confronto.pdf')
plt.show() 

