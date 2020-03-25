// mpi includes
#include <mpi.h>

// std includes
#include <vector>
#include <iostream>

int
main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int numRanks;
  MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  std::vector<double> v(100);

  if (rank == 0) {
    // send stuff from rank 0
    for (auto i=0; i<v.size(); ++i)
      v[i] = 0.5*i;

    // send to all other ranks
    for (auto r=1; r<numRanks; ++r)
      MPI_Send(&v[0], v.size(), MPI_DOUBLE, r, 22, MPI_COMM_WORLD);
  }
  else {
    // get stuff from rank-0
    MPI_Recv(&v[0], v.size(), MPI_DOUBLE, 0, 22, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // sum array as test
    double sum = 0.0;
    for (auto i=0; i<v.size(); ++i) sum += v[i];
    std::cout << "Rank " << rank << ": " << sum << std::endl;
  }

  MPI_Finalize();
  return 0;
}
