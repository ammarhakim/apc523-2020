CC = mpicxx -std=c++17 # C compiler to use
OPT = -O3 # optimization flags

# MPI include library path
MPI_INCLUDES = 
# Library paths
LIB_PATH = 
# Libraries
LIBS = 

all: advection

advection: advection.o
	$(CC) $(OPT) $(LIB_PATH) $(LIBS) advection.o -o advection

advection.o: advection.cpp NameValuePair.h
	$(CC) $(OPT) -I. $(MPI_INCLUDES) -c advection.cpp

clean:
	rm -rf $(ALL) *.o
