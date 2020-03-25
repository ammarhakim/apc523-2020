ALL = cnaive ctranspose ceigen ceigen-float csimdi csimdi-func.o cnosimdi-func.o
OPT = -O3 
INCLUDES = -I. -I /Users/ahakim/gkylsoft/eigen-3.3.7/include/eigen3

all: $(ALL)

cnaive: cnaive.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) cnaive.cpp -o cnaive

ctranspose: ctranspose.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) ctranspose.cpp -o ctranspose

ceigen: ceigen.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) ceigen.cpp -o ceigen

ceigen-float: ceigen-float.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) ceigen-float.cpp -o ceigen-float

csimdi: csimdi.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) csimdi.cpp -o csimdi

csimdi-func.o: csimdi-func.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) -c csimdi-func.cpp

cnosimdi-func.o: cnosimdi-func.cpp
	clang++ -std=c++17 $(OPT) $(INCLUDES) -c cnosimdi-func.cpp

clean:
	rm -rf $(ALL)
