# Building and running on Adroit

Everyone with a Tiger ID should have access to "adroit", Princeton
University's training cluster. You need to enable Duo Authenticate to
access Adroit. Log on to Adroit with your Tiger ID name:

```
ssh -Y tigerid@adroit.princeton.edu
```

Adroit (and all PU clusters) use a module system to load software
packages. You need to load the compilers and MPI libraries. Run the
following, or add them to your ```.basrc`` file.

```
module load intel
module load intel-mpi
```

Now clone the repo for the lectures and code as follows:

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

