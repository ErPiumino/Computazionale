import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize=(15, 12), dpi=80)
plt.title('Probability of self avoiding random walks trapped')
x, y = np.loadtxt("/workspaces/Computazionale2/Lab5/File/SelfAvoidingP.dat", unpack=True)
plt.scatter(y, x/5000, s=45, label='Trapped trajectories', color='r', marker='x')
#plt.plot(x, y, linestyle=':', color='grey', alpha=0.5)
plt.ylabel('Probability', fontsize=15)
plt.xlabel('Number of steps', fontsize=15)
plt.legend(fontsize=15)
plt.savefig('SelfAvoidingP.png')