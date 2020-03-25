ALL = sumsquares mpiskel
OPT = -O3 
INCLUDES = -I. -I/Users/ahakim/gkylsoft/openmpi/include
LIB = -L/Users/ahakim/gkylsoft/openmpi/lib -lmpi

all: $(ALL)

sumsquares: sumsquares.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) sumsquares.cpp
	clang++ sumsquares.o $(LIB) -o sumsquares

mpiskel: mpiskel.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) mpiskel.cpp
	clang++ mpiskel.o $(LIB) -o mpiskel

clean:
	rm -rf $(ALL)
