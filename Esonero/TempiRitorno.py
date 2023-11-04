# Importing libraries
import matplotlib as mat
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter, FuncFormatter, MultipleLocator
import numpy as np 

plt.figure(figsize=(12, 6))
x, y=np.loadtxt("TempiRitorno.dat",unpack=True)
y1 = y[1:]
plt.plot(x, y, color='skyblue', alpha=0.8)
plt.scatter(x, y, color='darkslategrey', label='Tempi di ritorno')
media1 = y.mean()
media2 = y1.mean()
plt.axhline(media1, color='blue', linestyle='--', label=f'Media con tutti i dati:{media1:.2f}')
plt.axhline(media2, color='cyan', linestyle='--', label=f'Media senza primo valore:{media2:.2f}')
plt.xlabel('Attraversamenti asse x')
plt.ylabel('Tempo di Ritorno (s)')
plt.legend(loc='lower right')
plt.xticks(np.arange(min(x), max(x)+1, 1.0))
plt.yticks(np.arange(min(y), max(y), 0.4))
plt.savefig('Parte0TempidiRitorno.pdf')