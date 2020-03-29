# Building and running on Adroit

Everyone with a Tiger ID should have access to "adroit", Princeton
University's training cluster.  You need to first set up a VPN
connection to vpn.princeton.edu which you probably already do.
(We recommend 
[SonicWall](https://princeton.service-now.com/snap?sys_id=6023&id=kb_article).
This involves using Duo Authenticate.) Assuming you have ssh 
installed on your computer, log on to Adroit with your Tiger
ID name:

```
ssh -Y tigerid@adroit.princeton.edu
```

Obviously, replace ```tigerid``` by your own Tiger ID. Adroit (and all
PU clusters) use a module system to load software packages. You need
to load the compilers, MPI libraries and Python for plotting. Run the
following, or add them to your ```.bashrc``` file.

```
module load intel
module load intel-mpi
module load anaconda
```

(Anaconda Python is a distribution of Python that contains
pre-packaged tools for computing and plotting). Now clone the repo for
the lectures and code as follows:

```
git clone https://github.com/ammarhakim/apc523-2020.git
```

Then cd to the code directory:

```
cd apc523-2020/code/advection/
```

To build the code simply type:

```
make
```

This will use the Intel C++ compiler to build the code and create the
executable ```advection```.

You can't run this executable on the head node, but need to get an
"interactive" queue. To do this, run:

```
salloc --ntasks=4 --time=00:10:00
```

This will allow you to run the job on at mode 4 cores for 10 minutes
or less. Once you get an interactive session you can run the advection
code:

```
mpiexec -n 2 ./advection advection.inp
```

The code will write 1 file per core. The initial conditions are
written to files ```advection-0_rX.txt``` and the final solution to
files ```advection-1_rX.txt```, where X is the rank number.

Plot the solution using:

```
python plot-sol.py -n 2
```

Pass the number of processors you used to run the simulation to the
```-n``` option.


For more information on using Adroit, see the
[Adroit tutorials](https://researchcomputing.princeton.edu/computational-hardware/adroit/tutorials).
