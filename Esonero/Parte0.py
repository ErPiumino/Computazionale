import matplotlib.pyplot as plt
import numpy as np

plt.title('Parte 0')
plt.xlabel('x')
plt.ylabel('y')
t, x, y = np.loadtxt('Parte0.dat', usecols=(0, 1, 2), unpack=True)
plt.plot(x, y, color='darkslategrey', label='x(t)')
plt.legend()
plt.savefig("Parte0.pdf")
plt.show()
