# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 
 
#plt.figure(figsize=(25, 50), dpi=80)
fig, axs = plt.subplots(2,2)
fig.set_figwidth(30)
fig.set_figheight(30)
fig.suptitle('Bacini di attrazione per varie $f0$', fontsize=35)
 
# Data per x(t) e v(t), bacini
x1black, v1black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.070Black.dat', usecols=(0, 1), unpack=True)
x1yellow, v1yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.070Yellow.dat', usecols=(0, 1), unpack=True)
x2black, v2black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Black.dat', usecols=(0, 1), unpack=True)
x2yellow, v2yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Yellow.dat', usecols=(0, 1), unpack=True)
x3black, v3black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.470Black.dat', usecols=(0, 1), unpack=True)
x3yellow, v3yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.470Yellow.dat', usecols=(0, 1), unpack=True)
x4black, v4black = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.500Black.dat', usecols=(0, 1), unpack=True)
x4yellow, v4yellow = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.500Yellow.dat', usecols=(0, 1), unpack=True)
axs[0,0].scatter(x1black, v1black, color='black', marker='.', s=2.5)
axs[0,0].scatter(x1yellow, v1yellow, color='yellow', marker='.', s=2.5)
axs[0,0].set_title('$F0=1.07, t^*=100.00$', fontsize=25)
axs[0,1].scatter(x2black, v2black, color='black', marker='.', s=2.5)
axs[0,1].scatter(x2yellow, v2yellow, color='yellow', marker='.', s=2.5)
axs[0,1].set_title('$F0=1.15, t^*=100.00$', fontsize=25)
axs[1,0].scatter(x3black, v3black, color='black', marker='.', s=2.5)
axs[1,0].scatter(x3yellow, v3yellow, color='yellow', marker='.', s=2.5)
axs[1,0].set_title('$F0=1.47, t^*=93.00$', fontsize=25)
axs[1,1].scatter(x4black, v4black, color='black', marker='.', s=2.5)
axs[1,1].scatter(x4yellow, v4yellow, color='yellow', marker='.', s=2.5)
axs[1,1].set_title('$F0=1.50, t^*=93.00$', fontsize=25)
for ax in axs.flat:
	ax.set(xlabel='$\\theta(0)$', ylabel='$d\\dot \\theta(0)$')
	ax.xaxis.get_label().set_fontsize(25)
	ax.yaxis.get_label().set_fontsize(25)
	ax.xaxis.set_major_formatter(FuncFormatter(
		lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
	))
	ax.xaxis.set_major_locator(MultipleLocator(base=np.pi/2))
	ax.yaxis.set_major_formatter(FuncFormatter(
		lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
	))
	ax.yaxis.set_major_locator(MultipleLocator(base=np.pi/2))
	ax.xlim=(-np.pi, np.pi)
	ax.ylim=(-np.pi, np.pi)
	ax.tick_params(axis='both', which='major', labelsize=25)
fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/Bacini.png')
