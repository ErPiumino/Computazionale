import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['axes.grid'] = True
fig, ax = plt.subplots(2)
fig.set_figwidth(12)
fig.set_figheight(12)
# Data and plot
t1, x1, y1 = np.loadtxt('Parte0dt0.01.dat', usecols=(0, 1, 2), unpack=True)
t2, x2, y2 = np.loadtxt('Parte0dt0.02.dat', usecols=(0, 1, 2), unpack=True)
t3, x3, y3 = np.loadtxt('Parte0dt0.03.dat', usecols=(0, 1, 2), unpack=True)
t4, x4, y4 = np.loadtxt('Parte0dt0.04.dat', usecols=(0, 1, 2), unpack=True)
ax[0].plot(t1, x1, color='darkslategrey', label='dt=0.01', alpha=0.4)
ax[0].plot(t2, x2, color='skyblue', label='dt=0.02', alpha=0.4)
ax[0].plot(t3, x3, color='blue', label='dt=0.03', alpha=0.4)
ax[0].plot(t4, x4, color='grey', label='dt=0.04', alpha=0.4)
ax[0].set_title('Traiettoria x(t) per vari dt', fontsize=12)
ax[0].set(xlabel='t', ylabel='x(t)')
ax[1].plot(t1, x1, color='darkslategrey', alpha=0.4)
ax[1].plot(t2, x2, color='skyblue', alpha=0.4)
ax[1].plot(t3, x3, color='blue', alpha=0.4)
ax[1].plot(t4, x4, color='grey', alpha=0.4)
ax[1].set_title('Traiettoria y(t) per vari dt', fontsize=12)
ax[1].set(xlabel='t', ylabel='y(t)')
handles, labels = ax[-1].get_legend_handles_labels()
for ax in ax[:-1]:
	h, l=ax.get_legend_handles_labels()
	handles += h
	labels += l
fig.legend(handles, labels, loc='upper right', bbox_to_anchor=(1, 0.57), fontsize=18)
fig.subplots_adjust(right=0.8, hspace=0.5)
plt.savefig("Parte0Traiettorie.pdf")