# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 
 
#plt.rcParams['axes.grid'] = True
#plt.figure(figsize=(25, 50), dpi=80)
fig, axs = plt.subplots(3,2)
fig.set_figwidth(15)
fig.set_figheight(15)
fig.suptitle('Sezioni di Poincare con Spazio delle fasi per varie $f0$', fontsize=25)
 
# Data per x(t) e v(t), spazio delle fasi
x1, v1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincareF00.900.dat', usecols=(0, 1), unpack=True)
x2, v2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincareF01.070.dat', usecols=(0, 1), unpack=True)
x3, v3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincareF01.150.dat', usecols=(0, 1), unpack=True)
x4, v4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincareF01.470.dat', usecols=(0, 1), unpack=True)
x5, v5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PendoloPoincareF01.500.dat', usecols=(0, 1), unpack=True)
# Data per i punti per la sezione di Poincarre
xp1, vp1 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF00.900.dat', usecols=(0, 1), unpack=True)
xp2, vp2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.070.dat', usecols=(0, 1), unpack=True)
xp3, vp3 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.150.dat', usecols=(0, 1), unpack=True)
xp4, vp4 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.470.dat', usecols=(0, 1), unpack=True)
xp5, vp5 = np.loadtxt('/workspaces/Computazionale/Lab4/File/PuntiPoincarreF01.500.dat', usecols=(0, 1), unpack=True)
axs[0,0].scatter(x1, v1, color='blue', marker='.', s=0.001)
axs[0,0].scatter(xp1, vp1, color='red', label='Poincarre', marker='.', s=25)
axs[0,0].legend(loc='upper left', fontsize=8)
axs[0,0].title.set_text('$F0=0.90$')
axs[0,1].scatter(x2, v2, color='blue', marker='.',  s=0.001)
axs[0,1].scatter(xp2, vp2, color='red', label='Poincarre', marker='.', s=25)
axs[0,1].legend(loc='upper left', fontsize=8)
axs[0,1].title.set_text('$F0=1.07$')
axs[1,0].scatter(x3, v3, color='blue', marker='.',  s=0.001)
axs[1,0].scatter(xp3, vp3, color='red', label='Poincarre', marker='.', s=25)
axs[1,0].legend(loc='upper left', fontsize=8)
axs[1,0].title.set_text('$F0=1.15$')
axs[1,1].scatter(x4, v4, color='blue', marker='.',  s=0.001)
axs[1,1].scatter(xp4, vp4, color='red', label='Poincarre', marker='.', s=25)
axs[1,1].legend(loc='upper left', fontsize=8)
axs[1,1].title.set_text('$F0=1.47$')
axs[2,0].scatter(x5, v5, color='blue', marker='.',  s=0.001)
axs[2,0].scatter(xp5, vp5, color='red', label='Poincarre', marker='.', s=25)
axs[2,0].legend(loc='upper left', fontsize=8)
axs[2,0].title.set_text('$F0=1.50$')
axs[2,1].set_visible(False)
for ax in axs.flat:
	ax.set(xlabel='$\\theta$', ylabel='$d\\theta/dt$')
	ax.xaxis.set_major_formatter(FuncFormatter(
		lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
	))
	ax.xaxis.set_major_locator(MultipleLocator(base=np.pi/2))
	ax.yaxis.set_major_formatter(FuncFormatter(
		lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
	))
	ax.yaxis.set_major_locator(MultipleLocator(base=np.pi/2))
	ax.grid()
	ax.set_axisbelow(True)
fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/PoincareSpazioFasi.pdf')
