import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

x,y=np.loadtxt("fit.dat",unpack=True)
log_x = np.fabs(np.log(x))
log_y = np.fabs(np.log(y))
params = np.polyfit(log_x, log_y, 1)
slope, intercept = params 
plt.scatter(log_x, log_y, label='Dati', marker='x', color='Darkslategrey')
plt.plot(log_x, slope*log_x+intercept, color='skyblue', label='fit scala logaritmica', alpha=0.8)

plt.xscale('log')
plt.yscale('log')

plt.xlabel('$dt$')
plt.ylabel('$e$')
print('Il coff angolare:',slope)
plt.savefig('FitVerlet.pdf')
plt.legend()
plt.show()
