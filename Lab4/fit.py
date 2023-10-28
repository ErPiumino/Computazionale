#Importing libraries
import matplotlib.pyplot as plt
import numpy as np 
from scipy.optimize import curve_fit 
 
#Codice per il fit
x,y=np.loadtxt('/workspaces/Computazionale/Lab4/File/fit.dat',unpack=True)
log_x = np.fabs(np.log10(x))
log_y = np.fabs(np.log10(y))
params = np.polyfit(log_x, log_y, 1)
#params = np.polyfit(x, y, 5)
a = params[0]
b = params[1]
plt.loglog(x, y, label=f'Dati, m={a:.2f}', marker='x', color='Darkslategrey')
#plt.loglog(x, 10**b * x**a, color='skyblue', label=f'm={a:.2f}', alpha=0.8)
#plt.plot(x,a*x**5 + b*x**4 + c*x**3 + d*x**2 + e*x + f, color='skyblue', label='fit lineare', alpha=0.8)
#plt.scatter(x, y, label='Dati', marker='x', color='Darkslategrey')
#m=np.fabs((y-b*x**4-c*x**3-d*x**2-e*x-f)/(x**5))
plt.xlabel('$dt$')
plt.ylabel('$e$')
#print('Il coff angolare:',m.mean())
print('Il coff angolare:',a)
plt.legend(loc='upper left')
plt.savefig('/workspaces/Computazionale/Lab4/Grafici/FitPendoloCaotico.pdf')
