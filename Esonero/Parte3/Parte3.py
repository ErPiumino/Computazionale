import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['axes.grid'] = True
fig, ax = plt.subplots(2,2)
fig.set_figwidth(30)
fig.set_figheight(30)
fig.suptitle('Studio di Equazione differenziale con attrito e con dt=0.01', fontsize=35)
# Data and plot
t, x, y, e = np.loadtxt('Parte3dt0.01.dat', usecols=(0, 1, 2, 3), unpack=True)
ax[0,0].plot(x, y, color='darkslategrey', label='(y(t), x(t))')
ax[0,0].set_title('Traiettoria', fontsize=25)
ax[0,0].set(xlabel='x(t)', ylabel='y(t)')
ax[0,1].plot(t, e, color='skyblue', label='e(t)')
ax[0,1].set_title('Conservazione', fontsize=25)
#ax[0,1].set_ylim(0.9999, 1.00025)
ax[0,1].set(xlabel='t', ylabel='e(t)')
ax[1,0].plot(t, x, color='blue', label='x(t)')
ax[1,0].set_title('Traiettoria x(t)', fontsize=25)
#ax[1,0].set_ylim(-3, 3)
ax[1,0].set(xlabel='t', ylabel='x(t)')
ax[1,1].plot(t, y, color='blue', label='y(t)')
ax[1,1].set_title('Traiettoria y(t)', fontsize=25)
#ax[1,1].set_ylim(-3, 3)
ax[1,1].set(xlabel='t', ylabel='y(t)')
for ax in ax.flat:
	ax.xaxis.get_label().set_fontsize(25)
	ax.yaxis.get_label().set_fontsize(25)
	ax.tick_params(axis='both', which='major', labelsize=25)
	ax.legend(loc='upper right', fontsize=25)
fig.subplots_adjust(left=0.1, bottom=0.1, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
plt.savefig("Parte3.pdf")