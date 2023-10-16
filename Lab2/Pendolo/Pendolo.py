# Importing libraries 
import matplotlib.pyplot as plt 
import numpy as np 
from scipy.optimize import curve_fit
  
fig, axs = plt.subplots(2)
fig.suptitle('Pendolo usando Verlet per vari $\Delta t$')

# Data per x(t)
x1, y1 = np.loadtxt('Pendolo0.0001.dat', usecols=(2, 0), unpack=True)
x2, y2 = np.loadtxt('Pendolo0.0002.dat', usecols=(2, 0), unpack=True)
x3, y3 = np.loadtxt('Pendolo0.0003.dat', usecols=(2, 0), unpack=True)
x4, y4 = np.loadtxt('Pendolo0.0004.dat', usecols=(2, 0), unpack=True)

# Data per E(t)
e1, te1 = np.loadtxt('Pendolo0.0001.dat', usecols=(2, 3), unpack=True)
e2, te2 = np.loadtxt('Pendolo0.0002.dat', usecols=(2, 3), unpack=True)
e3, te3 = np.loadtxt('Pendolo0.0003.dat', usecols=(2, 3), unpack=True)
e4, te4 = np.loadtxt('Pendolo0.0004.dat', usecols=(2, 3), unpack=True)

axs[0].plot(x1, y1, color='darkslategrey', label='$\Delta t = 0.0001 \ s$', alpha=0.5)
axs[0].plot(x2, y2, color='blue', label='$\Delta t = 0.0002 \ s$', alpha=0.5)
axs[0].plot(x3, y3, color='cyan', label='$\Delta t = 0.0003 \ s$', alpha=0.5)
axs[0].plot(x4, y4, color='skyblue', label='$\Delta t = 0.0004 \ s$', alpha=0.5)
axs[0].set(xlabel='$t$', ylabel='$x(t)$')
axs[1].plot(e1, te1, color='darkslategrey', label='$\Delta t = 0.0001 \ s$', alpha=0.5)
axs[1].plot(e2, te2, color='blue', label='$\Delta t = 0.0002 \ s$', alpha=0.5)
axs[1].plot(e3, te3, color='cyan', label='$\Delta t = 0.0003 \ s$', alpha=0.5)
axs[1].plot(e4, te4, color='skyblue', label='$\Delta t = 0.0004 \ s$', alpha=0.5)
axs[1].set(xlabel='$t$', ylabel='$E(t)$')
for ax in axs.flat:
    ax.legend(loc='upper left')
    ax.ticklabel_format(useOffset=False)
plt.tight_layout() 
plt.savefig('Pendolo.pdf')
plt.show() 

#Codice per il fit
x,y=np.loadtxt("FitPendolo.dat",unpack=True)
log_x = np.fabs(np.log(x))
log_y = np.fabs(np.log(y))
params = np.polyfit(log_x, log_y, 1)
slope, intercept = params 
plt.scatter(log_x, log_y, label='Dati', marker='x', color='Darkslategrey')
plt.plot(log_x, slope*log_x+intercept, color='skyblue', label='fit scala logaritmica', alpha=0.8)

plt.xscale('log')
plt.yscale('log')

plt.xlabel('$dt$')
plt.ylabel('$e$')
print('Il coff angolare:',slope)
plt.text(5.5, 14, '$m=2.0184$', fontsize = 10)
plt.legend(loc='upper left')
plt.savefig('FitPendolo.pdf')
plt.show()
