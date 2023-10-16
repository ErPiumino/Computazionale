import matplotlib.pyplot as plt
import numpy as np

plt.title('Eulero')
plt.xlabel('x')
plt.ylabel('y')
x, y = np.loadtxt('Eulero.dat', usecols=(2, 0), unpack=True)
t, v = np.loadtxt('Eulero.dat', usecols=(2, 1), unpack=True)
plt.plot(x, y, color='darkslategrey', label='x(t)')
plt.plot(t, v, color='r', label='v(t)')
plt.legend()
plt.savefig("Oscillatore_traiettoria.pdf")
plt.show()

x, y = np.loadtxt('Eulero.dat', usecols=(2, 3), unpack=True)
plt.plot(x, y, color='darkslategrey', label='E(t)')
plt.legend()
plt.savefig("Oscillatore_Energia.pdf")
plt.show()
