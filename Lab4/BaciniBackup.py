# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 
 
def colore(s2):
    for s2 in s2:
        color = []
        if s2 == 0: color.append("black") 
        else: color.append("yellow")         
    return color

# Data per x(t) e v(t), bacini
x2, v2, s2 = np.loadtxt('/workspaces/Computazionale/Lab4/File/BaciniF01.150.dat', usecols=(0, 1, 2), unpack=True)
segno = colore(s2)
plt.scatter(x2, v2, color=segno, marker='.')
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/BaciniProva.png')
