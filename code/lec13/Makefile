all: cnaive ctranspose ceigen

cnaive: cnaive.cpp
	clang++ -std=c++17 -O3 -I. cnaive.cpp -o cnaive

ctranspose: ctranspose.cpp
	clang++ -std=c++17 -O3 -I. ctranspose.cpp -o ctranspose

ceigen: ceigen.cpp
	clang++ -std=c++17 -O3 -I. -I /Users/ahakim/gkylsoft/eigen-3.3.7/include/eigen3 ceigen.cpp -o ceigen

clean:
	rm -rf cnaive ctranspose ceigen
