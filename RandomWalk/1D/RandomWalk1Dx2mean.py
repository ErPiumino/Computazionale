import matplotlib.pyplot as plt
import numpy as np
from matplotlib.pyplot import figure

figure(figsize=(20, 15), dpi=80)
plt.title('behavior of $<x(t)^2>$ in logaritmic scale', fontsize=20)
x, t= np.loadtxt('/workspaces/Computazionale2/Lab5/File/<x2>.dat', usecols=(0, 2), unpack=True)
#Vari plot
#plt.errorbar(t, x, yerr=err, alpha=0.5, label='Error')
plt.plot(np.linspace(0, np.max(t)), np.linspace(0, np.max(t)), color='grey',  zorder=-1, linestyle='--')
plt.scatter(t, x, color='skyblue', label='$<x(t)^2>$',  zorder=1, s=10)
plt.loglog([], [], '', label='5000 walks', alpha=0)
plt.legend(fontsize=20)
plt.xlabel=('t')
plt.ylabel=('$x(t)^2$')
#plt.axis(xmin=1, ymin=1)
plt.savefig("RandomWalk1Dx2mean.png")
