import matplotlib.pyplot as plt 
import numpy as np 
from scipy.optimize import curve_fit

#Codice per il fit
x,y=np.loadtxt("fit.dat",unpack=True)
log_x = np.fabs(np.log(x))
log_y = np.fabs(np.log(y))
#params = np.polyfit(log_x, log_y, 1)
params = np.polyfit(x, y, 1)
a, b = params
#plt.scatter(log_x, log_y, label='Dati', marker='x', color='Darkslategrey')
#plt.plot(log_x, a*log_x + b, color='skyblue', label='fit scala logaritmica', alpha=0.8)
plt.plot(x, y, color='skyblue', label='fit lineare', alpha=0.8)
plt.scatter(x, y, label='Dati', marker='x', color='Darkslategrey')

#plt.xscale('log')
#plt.yscale('log')

m=np.fabs((np.log(y)-b)/np.log(x))

plt.xlabel('$dt$')
plt.ylabel('$e$')
print('Il coff angolare:',m.mean())
#plt.text(5.5, 14, '$m=2.0184$', fontsize = 10)
plt.legend(loc='upper left')
plt.savefig('FitPendolo.pdf')
plt.show()
