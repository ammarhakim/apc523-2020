all: cnaive ctranspose ceigen ceigen-float csimdi csimdi-func.o cnosimdi-func.o

cnaive: cnaive.cpp
	clang++ -std=c++17 -O3 -I. cnaive.cpp -o cnaive

ctranspose: ctranspose.cpp
	clang++ -std=c++17 -O3 -I. ctranspose.cpp -o ctranspose

ceigen: ceigen.cpp
	clang++ -std=c++17 -O3 -I. -I /Users/ahakim/gkylsoft/eigen-3.3.7/include/eigen3 ceigen.cpp -o ceigen

ceigen-float: ceigen-float.cpp
	clang++ -std=c++17 -O3 -I. -I /Users/ahakim/gkylsoft/eigen-3.3.7/include/eigen3 ceigen-float.cpp -o ceigen-float

csimdi: csimdi.cpp
	clang++ -std=c++17 -O3 -I. csimdi.cpp -o csimdi

csimdi-func.o: csimdi-func.cpp
	clang++ -std=c++17 -O3 -I. -c csimdi-func.cpp

cnosimdi-func.o: cnosimdi-func.cpp
	clang++ -std=c++17 -O3 -I. -c cnosimdi-func.cpp

clean:
	rm -rf cnaive ctranspose ceigen csimdi csimdi-func.o cnosimdi-func.o
