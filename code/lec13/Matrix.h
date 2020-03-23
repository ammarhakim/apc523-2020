#pragma once

#include <vector>
#include <random>
#include <cmath>
#include <cfloat>

class Matrix {
  public:
    Matrix(unsigned N, unsigned M) : N(N), M(M), m(N*M) { }
    inline const double operator()(unsigned i, unsigned j) const { return m[i*N+j]; }
    inline double& operator()(unsigned i, unsigned j) {  return m[i*N+j]; }

    unsigned numRows() const { return N; }
    unsigned numCols() const { return M; }

    // initalize with random numbers
    void random() {
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_real_distribution<double> dist(-1000.0, std::nextafter(1000.0, DBL_MAX));
      for (auto i=0; i<N; ++i)
        for (auto j=0; j<M; ++j)
          this->operator()(i,j) = dist(mt);
    }

  private:
    unsigned N, M;
    std::vector<double> m;
};
