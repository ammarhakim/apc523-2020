// Simple 1D advection equation solver. Works in parallel and uses
// periodic BCs

// advection includes
#include <NameValuePair.h>

// mpi includes
#include <mpi.h>

#define _USE_MATH_DEFINES
// std includes
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/** Finalize MPI */
int
finalize(int status) {
  MPI_Finalize();
  return status;
}

/* Return rank for current processor */
int
getRank() {
  int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  return rank;
}

/** Struct to store simulation input data */
struct SimData {
    /** Lower and upper edge of domain */
    double lower, upper;
    /** Number of cells */
    unsigned N;
    /** Advection speed */
    double speed;
    /** CFL number */
    double cfl;
    /** Simulation end time */
    double tEnd;
};

/** Structure to represent sub-domain grid */
struct Grid {
    /** Lower and upper edge of sub-domain */
    double lower, upper;
    /** Numer of cells */
    unsigned cells;
    /** Cell spacing */
    double dx;
};

/** Initial condition function 
 *
 * @param nvPair Input file parsed values
 * @param x Coordinate
 * @return initial condition
 *
 */
double
initFunc(const NameValuePair& nvPair, double x) {
  return std::sin(2*M_PI*x);
}

/**
 * Decompose grid.
 *
 * @param simData Simulation input
 */
Grid
decomposeGrid(const SimData& simData) {
  int numRanks; MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
  int rank = getRank();

  unsigned quot = simData.N/numRanks, rem = simData.N % numRanks;

  // start index into grid for each rank
  std::vector<unsigned> startIdx(numRanks);
  startIdx[0] = 0;

  // compute local start index into global grid for all ranks
  for (unsigned i=1; i<numRanks; ++i)
    if (i <= rem)
      startIdx[i] = startIdx[i-1]+(quot+1); // give lower ranks remainder cells
    else
      startIdx[i] = startIdx[i-1]+quot;

  Grid grid;

  // number of cells in local domain
  grid.cells = rank < rem ? quot+1 : quot;

  // lower/upper of local domain
  grid.dx = (simData.upper-simData.lower)/simData.N;  
  grid.lower = grid.dx*startIdx[rank];
  grid.upper = grid.dx*(startIdx[rank]+grid.cells);

  return grid;
}

/**
 * Apply initial condition.
 *
 * @param nvPair Input file parsed values
 * @param grid Local grid
 * @param f Field to initialize
 */
void
applyInitCondition(const NameValuePair& nvPair, const Grid& grid, std::vector<double>& f) {
  // initialize cell-center values for interior cells (1 ... cells)
  for (auto i=1; i<=grid.cells; ++i) {
    double x = grid.lower + (i-0.5)*grid.dx;
    f[i] = initFunc(nvPair, x);
  }
}

/**
 * Write solution to file
 *
 * @param grid Grid object
 * @param f Field to write out
 * @param frame Frame number
 */
void
writeField(const Grid& grid, const std::vector<double>& f, unsigned frame) {
  int rank = getRank();
  std::ostringstream fName;
  fName << "advection-" << frame << "_r" << rank << ".txt";

  // open output file
  std::ofstream outFile(fName.str());

  outFile << "# " << "x " << " value" << std::endl;
  // write data to file
  for (auto i=1; i<=grid.cells; ++i) {
    double x = grid.lower + (i-0.5)*grid.dx;
    outFile << x << " " << f[i] << std::endl;
  }  
}

/**
 * Synchronize fields by copying skin-cells to ghost cells
 *
 * @param f Field to synchronize
 */
void
syncField(std::vector<double>& f) {
}

/**
 * Advance solution by dt
 * 
 * @param dt Time-step
 * @param simData Simulation data
 * @param grid Grid object
 * @param fIn Solution at current time-step
 * @param fOut Solution at next time-step
 */
void
advanceByDt(double dt, const SimData& simData, const Grid& grid, const std::vector<double>& fIn, std::vector<double>& fOut) {
  double dx = grid.dx;
  double speed = simData.speed;
  // loop over interior cells, updating solution
  for (auto i=1; i<=grid.cells; ++i)
    fOut[i] = fIn[i] - speed*dt/(2*dx)*(fIn[i+1]-fIn[i-1]);
}

/** Run simulation 
 *
 * @param simData Simulation input
 */
void
runSim(const NameValuePair& nvPair, const SimData& simData) {
  // decompose grid
  Grid grid = decomposeGrid(simData);

  // allocate memory to store solution: cell 0 and 'grid.cells' are ghost cells
  std::vector<double> f(grid.cells+2); // +2 for ghost-cells
  std::vector<double> fNew(f.size()); // solution at next time-step
  
  // apply initial conditions
  applyInitCondition(nvPair, grid, f);
  
  // write initial conditions to file
  writeField(grid, f, 0);

  double dx = grid.dx;
  double speed = simData.speed;
  // compute time-step based on CFL number
  double dt = simData.cfl*dx/speed;

  double tCurr = 0.0, tEnd = simData.tEnd;
  bool isDone = false;
  unsigned step = 1;
  int rank = getRank();
  
  // main loop: advance solution to tEnd
  while (!isDone) {
    // sync field across processors before taking a step
    syncField(f);

    double myDt = dt;
    if (tCurr+dt > tEnd) {
      // adjust time-step to hit tEnd exactly
      myDt = tEnd-tCurr;
      isDone = true;
    }
    if (rank == 0)
      std::cout << "Taking time-step " << step << " with dt " << myDt << std::endl;
    
    // advance solution by one time-step
    advanceByDt(myDt, simData, grid, f, fNew);
    f = fNew;
    tCurr += myDt;
    step += 1;
  }

  // write final solution to file
  writeField(grid, f, 1);
}

int
main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  // ensure correct number of parameters are specified
  if (argc != 2) {
    std::cout << "Usage: " << std::endl;
    std::cout << "advection inp-file" << std::endl;
    std::cout << "  inp-file  Name of input file" << std::endl;
    return finalize(0);
  }

  try {
    // parse input file and populate simulation data object
    NameValuePair nvPair = NameValuePair(argv[1]);

    SimData simData;
    simData.lower = nvPair.getValue("lower");
    simData.upper = nvPair.getValue("upper");
    simData.N = nvPair.getValue("N");
    simData.cfl = nvPair.getValue("cfl");
    simData.tEnd = nvPair.getValue("tEnd");
    simData.speed = nvPair.getValue("speed");
    
    runSim(nvPair, simData);
  }
  catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }

  return finalize(0);
}
