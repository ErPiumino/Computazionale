# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 
import matplotlib.patches as mpatches

V0 = [2.06, 2.23, 2.82, 1.44, 2.69, 1.20, 1.32, 1.97]
theta = [0.30, 0.75, 0.70, 0.08, 0.07, 0.16, 0.41, 0.01]

fig, ax = plt.subplots(1)
fig.set_figwidth(30)
fig.set_figheight(30)
x1, y1=np.loadtxt("ParteExtrax>1.dat",unpack=True)
x2, y2=np.loadtxt("ParteExtrax<1.dat",unpack=True)
ax.scatter(x1, y1, color='black', label='x(100)>1', s=10)
ax.scatter(x2, y2, color='yellow', label='x(100)<1', s=10)
ax.scatter(V0[0], theta[0], s=1000, linewidth=10, facecolors='none', edgecolors='grey')
plt.text(V0[0]+0.01, theta[0]+0.01, f'({V0[0]:.2f};{theta[0]:.2f})' , fontsize=30, color='grey', weight='bold')
ax.scatter(V0[1], theta[1], s=1000, linewidth=10, facecolors='none', edgecolors='red')
plt.text(V0[1]+0.01, theta[1]+0.01, f'({V0[1]:.2f};{theta[1]:.2f})' , fontsize=30, color='red', weight='bold')
ax.scatter(V0[2], theta[2], s=1000, linewidth=10, facecolors='none', edgecolors='blue')
plt.text(V0[2]+0.01, theta[2]+0.01, f'({V0[2]:.2f};{theta[2]:.2f})' , fontsize=30, color='blue', weight='bold')
ax.scatter(V0[3], theta[3], s=1000, linewidth=10, facecolors='none', edgecolors='grey')
plt.text(V0[3]+0.01, theta[3]+0.01, f'({V0[3]:.2f};{theta[3]:.2f})' , fontsize=30, color='grey', weight='bold')
ax.scatter(V0[4], theta[4], s=1000, linewidth=10, facecolors='none', edgecolors='cyan')
plt.text(V0[4]+0.01, theta[4]+0.01, f'({V0[4]:.2f};{theta[4]:.2f})' , fontsize=30, color='cyan', weight='bold')
ax.scatter(V0[5], theta[5], s=1000, linewidth=10, facecolors='none', edgecolors='orange')
plt.text(V0[5]+0.01, theta[5]+0.01, f'({V0[5]:.2f};{theta[5]:.2f})' , fontsize=30, color='orange', weight='bold')
ax.scatter(V0[6], theta[6], s=1000, linewidth=10, facecolors='none', edgecolors='green')
plt.text(V0[6]+0.01, theta[6]+0.01, f'({V0[6]:.2f};{theta[6]:.2f})' , fontsize=30, color='green', weight='bold')
ax.scatter(V0[7], theta[7], s=1000, linewidth=10, facecolors='none', edgecolors='magenta')
plt.text(V0[7]+0.01, theta[7]+0.01, f'({V0[7]:.2f};{theta[7]:.2f})' , fontsize=30, color='magenta', weight='bold')
ax.set(xlabel='$v(0)$', ylabel="$\\theta (0)$")
ax.xaxis.get_label().set_fontsize(35)
ax.yaxis.get_label().set_fontsize(35)
ax.yaxis.set_major_formatter(FuncFormatter(
	lambda val,pos: '{:.0g}$\pi$'.format(val/np.pi) if val !=0 else '0'
))
ax.yaxis.set_major_locator(MultipleLocator(base=np.pi/8))
ax.tick_params(axis='both', which='major', labelsize=35)
patch1 = mpatches.Patch(color='black', label='$x(100)>1$')
patch2 = mpatches.Patch(color='yellow', label='$x(100)<1$')
plt.legend(handles=[patch1, patch2], loc='lower left', fontsize=35)
plt.savefig('Baciniconpunti.png')