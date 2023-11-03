# Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
 
plt.title('Sezione di Poincarre per varie F0')
plt.xlabel('$\\theta$')
plt.ylabel('$d\\theta/dt$')
xp1, vp1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF00.900.dat', usecols=(0, 1), unpack=True)
xp2, vp2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.070.dat', usecols=(0, 1), unpack=True)
xp3, vp3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.150.dat', usecols=(0, 1), unpack=True)
xp4, vp4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.470.dat', usecols=(0, 1), unpack=True)
xp5, vp5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.500.dat', usecols=(0, 1), unpack=True)
plt.scatter(xp1, vp1, color='darkslategrey', marker='.', s=50, label='$F0 = 0.90$')
plt.scatter(xp2, vp2, color='blue', marker='.', s=50, label='$F0 = 1.07$')
plt.scatter(xp3, vp3, color='green', marker='.', s=1, label='$F0 = 1.15$')
plt.scatter(xp4, vp4, color='skyblue', marker='.', s=50, label='$F0 = 1.47$')
plt.scatter(xp5, vp5, color='red', marker='.', s=1, label='$F0 = 1.50$')
plt.legend(loc='upper left')
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/Poincare.pdf')
