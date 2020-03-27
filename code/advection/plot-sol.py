from pylab import *

numRanks = 1

figure(1)
for i in range(numRanks):
    f0 = loadtxt("advection-0_r%d.txt" % i)
    plot(f0[:,0], f0[:,1], 'r-')
    
    f1 = loadtxt("advection-1_r%d.txt" % i)
    plot(f1[:,0], f1[:,1], 'k-')
    
grid()
show()

