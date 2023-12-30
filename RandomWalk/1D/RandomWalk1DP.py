import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=(15, 12), dpi=80)
plt.title("Probability distribution of 1D Random Walk for various t", fontsize=15)
x1, y1 = np.loadtxt("/workspaces/Computazionale2/RandomWalk/File/RW1DPt=1000.dat", usecols=(0,1), unpack=True)
x2, y2 = np.loadtxt("/workspaces/Computazionale2/RandomWalk/File/RW1DPt=10000.dat", usecols=(0,1), unpack=True)
x3, y3 = np.loadtxt("/workspaces/Computazionale2/RandomWalk/File/RW1DPt=100000.dat", usecols=(0,1), unpack=True)
plt.scatter(x1, y1, marker='x', s=35, label=f'$t=10^3$')
plt.scatter(x2, y2, marker='^', s=35, label=f'$t=10^4$')
plt.scatter(x3, y3, marker='D', s=35, label=f'$t=10^5$')
plt.plot([], [], '', label='Number of simulation = 1000', alpha=0)
plt.legend(fontsize=15)
plt.xlabel('x', fontsize=15)
plt.ylabel('P(t)', fontsize=15)
plt.savefig("RandomWalk1DP.png")