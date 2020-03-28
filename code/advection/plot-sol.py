from pylab import *
import argparse

parser = argparse.ArgumentParser(description='Plot solution from advection code')
parser.add_argument('-n', dest='numRanks', action='store', required=True,
                    type=int,
                    help='Number of ranks use to run simulation')
args = parser.parse_args()
numRanks = args.numRanks

figure(1)
for i in range(numRanks):
    f0 = loadtxt("advection-0_r%d.txt" % i)
    plot(f0[:,0], f0[:,1], 'r-')
    
    f1 = loadtxt("advection-1_r%d.txt" % i)
    plot(f1[:,0], f1[:,1], 'k-')

title('Red: Initial Condition. Black: Solution')
grid()
show()

