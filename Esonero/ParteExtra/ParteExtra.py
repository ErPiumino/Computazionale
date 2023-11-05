# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 
import matplotlib.patches as mpatches

fig, ax = plt.subplots(1)
fig.set_figwidth(30)
fig.set_figheight(30)
x1, y1=np.loadtxt("ParteExtray>0.dat",unpack=True)
x2, y2=np.loadtxt("ParteExtray<0.dat",unpack=True)
ax.scatter(x1, y1, color='black', label='x(100)>1', s=10)
ax.scatter(x2, y2, color='yellow', label='x(100)<1', s=10)
ax.set(xlabel='$v(0)$', ylabel='$\\theta(0)$')
ax.xaxis.get_label().set_fontsize(35)
ax.yaxis.get_label().set_fontsize(35)
ax.yaxis.set_major_formatter(FuncFormatter(
	lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
))
ax.yaxis.set_major_locator(MultipleLocator(base=np.pi/8))
ax.tick_params(axis='both', which='major', labelsize=35)
patch1 = mpatches.Patch(color='black', label='$x(100)>0$')
patch2 = mpatches.Patch(color='yellow', label='$x(100)<0$')
plt.legend(handles=[patch1, patch2], loc='lower left', fontsize=35)
plt.savefig('Baciniy.png')