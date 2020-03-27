CC = clang++ -std=c++17 # C compiler to use
OPT = -O3 # optimization flags

# MPI include library path
MPI_INCLUDES = -I/Users/ahakim/gkylsoft/openmpi/include
# Library paths
LIB_PATH = -L/Users/ahakim/gkylsoft/openmpi/lib
# Libraries
LIBS = -lmpi

all: advection

advection: advection.o
	$(CC) $(OPT) $(LIB_PATH) $(LIBS) advection.o -o advection

advection.o: advection.cpp NameValuePair.h
	$(CC) $(OPT) -I. $(MPI_INCLUDES) -c advection.cpp

clean:
	rm -rf $(ALL) *.o
