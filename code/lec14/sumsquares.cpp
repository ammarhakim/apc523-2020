// mpi includes
#include <mpi.h>

// std includes
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

double
mapReduce(const std::vector<double>& a) {
  // compute sum of our local array
  double mySum = 0.0;
  for (unsigned i=0; i<a.size(); ++i)
    mySum += 1/std::pow(2,a[i]);
  
  // now sum across all processors
  double sum; // this will hold the total value

  MPI_Allreduce(&mySum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  return sum;
}

int
main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  unsigned N = 21; // total number of elements

  // determine number of ranks
  int numRanks;
  MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
  
  // determine our rank
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  unsigned quot = N/numRanks; // quotient
  unsigned rem = N % numRanks; // remainder

  // start indices into arrays for each rank
  std::vector<unsigned> startIdx(numRanks);
  startIdx[0] = 0;

  // adjust number of elements to make sure we handle all N elements
  for (unsigned i=1; i<numRanks; ++i)
    if (i <= rem)
      startIdx[i] = startIdx[i-1]+(quot+1); // give lower ranks left over work
    else
      startIdx[i] = startIdx[i-1]+quot;

  // number of elements handled by each rank
  unsigned myN = rank < rem ? quot+1 : quot;

  // allocate local memory
  std::vector<double> a(myN), b(myN);

  // construct array of values
  for (unsigned i=0; i<myN; ++i)
      a[i] = startIdx[rank]+i;

  // apply map-reduce to array
  double sum = mapReduce(a);

  // write out result only on rank-0
  if (rank == 0)
    std::cout << "Sum is " << std::setprecision(16) << sum << std::endl;

  MPI_Finalize();
  return 0;
}
