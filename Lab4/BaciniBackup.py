# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 

fig, axs = plt.subplots()
fig.set_figwidth(25)
fig.set_figheight(25)
# Data per x(t) e v(t), bacini
xnero, vnero = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Nero.dat', usecols=(0, 1), unpack=True)
xrosso, vrosso = np.loadtxt('/workspaces/Computazionale/Lab4/File/Bacini/BaciniF01.150Rosso.dat', usecols=(0, 1), unpack=True)
axs.scatter(xnero, vnero, color='yellow', marker='.', s=25)
axs.scatter(xrosso, vrosso, color='black', marker='.', s=25)
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/BaciniProva.pdf')
