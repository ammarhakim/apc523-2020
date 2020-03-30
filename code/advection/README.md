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
ssh -X tigerid@adroit.princeton.edu
```

Obviously, replace ```tigerid``` by your own Tiger ID. Adroit (and all
PU clusters) use a module system to load software packages. For more
information on using Adroit, see the [Adroit
tutorials](https://researchcomputing.princeton.edu/computational-hardware/adroit/tutorials).


You need to load the compilers, MPI libraries and Python for
plotting. Run the following, or add them to your ```.bashrc``` file.

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
salloc --ntasks=4 --time=00:10:00 --x11
```

This will allow you to run the job on at most 4 cores for 10 minutes
or less. Once you get an interactive session (there is usually only 
a few seconds delay) you can run the advection code:

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

After you finish your interactive sesion with the 4 cores, type 
"exit" to return to your login session on the head node.

In order for the plotting to work, you need an "X Windows" server
installed on your local computer.  On a Mac, you can download and
install the [XQuartz
server](https://support.apple.com/en-us/HT201341).  There are also X
Windows servers (such as Xming) that can be installed for PCs. Linux
machines have X Windows by default. If you have a hard time getting an
X Windows server, a workaround is to ship the output files to your own
computer and run the python plotting script on it.

An alternative to plotting using X Windows from Adroit to your
computer is to use "MyAdroit":

In a browser, go to myadroit.princeton.edu and login.  You can click
on the "Desktop" interactive app, and leave all of the options at the
default, using just 1 core.  This gives you a virtual desktop running
on Adroit.  (Steve Jobs got the idea for the Mac desktop from seeing
a GUI-based desktop on a Unix computer at Xerox.)  (In addition to
plotting, you can use one of the simple file editors on the virtual
desktop if you aren't familiar with command-line based editors like
emacs or Vim.)

Click on the Terminal icon on the top bar.  In the terminal type

```
module add anaconda
```

(It's not clear to me how they have configured things for myadroit.
"module load intel" doesn't work.  It seems you still need to have a
separate terminal connection from your computer to an adroit login
node to be able to compile the code on a long in node and then run
it in parallel in a slurm interactive session.  But plotting is much
faster on myadroit.)

Move to the subdirectory where the code is, and plot:

```
cd apc523-2020/code/advection
python plot-sol.py -n 2
```

When you are finished, on the top bar click System -> Log Out.
