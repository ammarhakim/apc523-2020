ALL = sumsquares mpiskel cpp-particle-push sendrecv
OPT = -O3 -funroll-loops
INCLUDES = -I. -I/Users/ahakim/gkylsoft/openmpi/include
LIB = -L/Users/ahakim/gkylsoft/openmpi/lib -lmpi

all: $(ALL)

mpiskel: mpiskel.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) mpiskel.cpp
	clang++ mpiskel.o $(LIB) -o mpiskel

sendrecv: sendrecv.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) sendrecv.cpp
	clang++ sendrecv.o $(LIB) -o sendrecv

sumsquares: sumsquares.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) sumsquares.cpp
	clang++ sumsquares.o $(LIB) -o sumsquares

cpp-particle-push: cpp-particle-push.cpp
	clang++ -std=c++17 -c $(INCLUDES) $(OPT) cpp-particle-push.cpp
	clang++ cpp-particle-push.o $(LIB) -o cpp-particle-push

clean:
	rm -rf $(ALL)
