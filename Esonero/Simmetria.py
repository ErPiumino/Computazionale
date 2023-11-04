# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 

fig, ax = plt.subplots(2)
fig.set_figwidth(15)
fig.set_figheight(8)
x, y = np.loadtxt("Parte0dt0.01.dat", usecols=(0, 1), unpack=True)
ax[0].plot(x, y, color='skyblue', alpha=0.8)
ax[0].axhline(0, color='black', linewidth=0.7)
ax[0].axvline(25.1900000000, color='darkslategrey', linestyle='--', linewidth=1)
ax[0].set(xlabel='t', ylabel='x(t)')
ax[0].set_xlim(0, 50.5)

ax[1].plot(x, y, color='skyblue', alpha=0.8)
ax[1].axvline(25.1900000000, color='darkslategrey', linestyle='--', linewidth=1)
ax[1].axvline(93.9900000000, color='darkslategrey', linestyle='--', linewidth=1)
ax[1].axvline(162.790000000, color='darkslategrey', linestyle='--', linewidth=1)
ax[1].set(xlabel='t', ylabel='x(t)')
ax[1].set_xlim(0, 200)
ax[1].set_xticks(np.arange(25, 200, 68.8))
fig.subplots_adjust(hspace=0.5)
plt.savefig('Simmetria.pdf')