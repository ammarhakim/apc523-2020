#include <Matrix.h>
#include <cfloat>
#include <chrono>
#include <cmath> 
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>
#include <vector>

void matmat(const Matrix& A, const Matrix& B, Matrix& C) {
  auto N = A.numRows(); // assume matrix is square
  
  for (auto i=0; i<N; ++i)
    for (auto j=0; j<N; ++j) {
      C(i,j) = 0.0;
      for (auto k=0; k<N; ++k)
        C(i,j) += A(i,k)*B(k,j);
    }
}

void test_matmat() {
  Matrix A(2,2), B(2,2), C(2,2);
  A(0,0) = 1.0; A(0,1) = 2.0;
  A(1,0) = 3.0; A(1,1) = 4.0;

  B(0,0) = 5.0; B(0,1) = 6.0;
  B(1,0) = 7.0; B(1,1) = 8.0;

  matmat(A, B, C); // [ [19,22], [43, 50] ]
  std::cout << C(0,0) << " " << C(0,1) << std::endl;
  std::cout << C(1,0) << " " << C(1,1) << std::endl;
}

void showUsage() {
  std::cout << "ctranspose -n nloop -N matrix-size" << std::endl;
}

int finish(int n) {
  return n;
}

int
main(int argc, char **argv) {
  unsigned nloop, N;
  bool runTest = false;
  
  char c;
  while ((c = getopt(argc, argv, "+htn:N:")) != -1)
    switch (c)
    {
      case 'h':
          showUsage();
          return finish(0);
          break;

      case 't':
          runTest = true;
          break;

      case 'n':
          nloop = std::stoi(optarg);
          break;
            
      case 'N':
          N = std::stoi(optarg);
          break;

      case '?':
          return finish(0);
    }

  if (runTest) {
    test_matmat();
    return finish(0);
  }
  
  Matrix A(N,N), B(N,N), C(N,N);
  A.random(); B.random();

  double sum = 0.0;
  auto startTm = std::chrono::steady_clock::now();
  for (auto n=0; n<nloop; ++n) {
    matmat(A, B, C);
    sum += C(0,0);
  }
  auto endTm = std::chrono::steady_clock::now();

  auto runTm = std::chrono::duration_cast<std::chrono::microseconds>(endTm-startTm).count();
  auto flops = N*N*N*nloop/(runTm*1e-6);
  std::cout << "Time " << runTm/1e6 << " s. MFLOPS " << flops/1e6
            << " (Sum " << sum/(N*N) << ")"
            << std::endl;
  
  return 0;
}
