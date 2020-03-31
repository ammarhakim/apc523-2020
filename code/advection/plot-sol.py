import pylab as pl
import argparse

parser = argparse.ArgumentParser(description='Plot solution from advection code')
parser.add_argument('-n', dest='numRanks', action='store', required=True,
                    type=int,
                    help='Number of ranks use to run simulation')
args = parser.parse_args()
numRanks = args.numRanks


pl.figure(1)
for i in range(numRanks):
    f0 = pl.loadtxt("advection-0_r%d.txt" % i)
    pl.plot(f0[:,0], f0[:,1], 'r-')
    
    f1 = pl.loadtxt("advection-1_r%d.txt" % i)
    pl.plot(f1[:,0], f1[:,1], 'k-')

pl.title('Red: Initial Condition. Black: Solution')
pl.grid()
pl.show()

