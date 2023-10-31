# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 

fig, axs = plt.subplots()
fig.set_figwidth(10)
fig.set_figheight(10)
# Data per x(t) e v(t), bacini
xnero, vnero = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Nero.dat', usecols=(0, 1), unpack=True)
xrosso, vrosso = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Rosso.dat', usecols=(0, 1), unpack=True)
axs.scatter(xnero, vnero, color='yellow', marker='.', s=1)
axs.scatter(xrosso, vrosso, color='black', marker='.', s=1)
axs.set(xlabel='$\\theta(0)$', ylabel='$\\dot\\theta(0)$')
axs.xaxis.set_major_formatter(FuncFormatter(
	lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
))
axs.xaxis.set_major_locator(MultipleLocator(base=np.pi/2))
axs.yaxis.set_major_formatter(FuncFormatter(
	lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
))
axs.yaxis.set_major_locator(MultipleLocator(base=np.pi/2))
axs.xlim=(-np.pi, np.pi)
axs.ylim=(-np.pi, np.pi)
#axs.spines[axs].set_linewidth(2.5)
#axs.tick_params(axis='both', which='major', labelsize=20, width=2.5, lenght=10)
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/BaciniProva.pdf')
