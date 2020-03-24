#include <Eigen/Dense>
#include <cfloat>
#include <chrono>
#include <cmath> 
#include <iostream>
#include <random>
#include <string>
#include <unistd.h>

void randomInit(Eigen::MatrixXf& m) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(-1000.0, std::nextafter(1000.0, DBL_MAX));
  for (auto i=0; i<m.rows(); ++i)
    for (auto j=0; j<m.cols(); ++j)
      m(i,j) = dist(mt);
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
  while ((c = getopt(argc, argv, "+hn:N:")) != -1)
    switch (c)
    {
      case 'h':
          showUsage();
          return finish(0);
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

  Eigen::MatrixXf A(N,N), B(N,N), C(N,N);
  randomInit(A); randomInit(B);

  float sum = 0.0;
  auto startTm = std::chrono::steady_clock::now();
  for (auto n=0; n<nloop; ++n) {
    C = A*B;
    sum += C(0,0);
  }
  auto endTm = std::chrono::steady_clock::now();

  auto runTm = std::chrono::duration_cast<std::chrono::microseconds>(endTm-startTm).count();
  auto flops = N*N*N*(nloop/(runTm*1e-6));
  std::cout << "Time " << runTm*1e-6 << " s. MFLOPS " << flops/1e6
            << " (Sum " << sum/(N*N) << ")"
            << std::endl;
  
  return 0;
}
