#include <iostream>
#include <ctime>
#include <vector>

typedef struct alignas(16) { double x[3], v[3]; } particle_t;

int
borisPush(double q, double m, double dt, const double E[3], const double B[3], std::vector<particle_t>& pList)
{
  int count = 0;
  double qmdt = 0.5*q/m*dt;
  double B_0 = B[0], B_1 = B[1], B_2 = B[2];
  double E_0 = E[0], E_1 = E[1], E_2 = E[0];

  for (unsigned pIdx=0; pIdx<pList.size(); ++pIdx)
  {
    double t_0 = qmdt*B_0;
    double t_1 = qmdt*B_1;
    double t_2 = qmdt*B_2;

    double tNorm1 = 1/(1+ t_0*t_0 + t_1*t_1 + t_2*t_2);
    double s_0 = 2*t_0*tNorm1;
    double s_1 = 2*t_1*tNorm1;
    double s_2 = 2*t_2*tNorm1;

    // half-step electric field update
    double vm_0 = pList[pIdx].v[0] + qmdt*E_0;
    double vm_1 = pList[pIdx].v[1] + qmdt*E_1;
    double vm_2 = pList[pIdx].v[2] + qmdt*E_2;

    // rotation around magnetic field (first compute cp = vm X t)
    double cp_0 =  vm_1*t_2 - vm_2*t_1;
    double cp_1 =  vm_2*t_0 - vm_0*t_2;
    double cp_2 =  vm_0*t_1 - vm_1*t_0;

    double vprime_0 = vm_0 + cp_0;
    double vprime_1 = vm_1 + cp_1;
    double vprime_2 = vm_2 + cp_2;
      
    // (first compute cp = vprime X s)
    cp_0 =  vprime_1*s_2 - vprime_2*s_1;
    cp_1 =  vprime_2*s_0 - vprime_0*s_2;
    cp_2 =  vprime_0*s_1 - vprime_1*s_0;

    double vp_0 = vm_0 + cp_0;
    double vp_1 = vm_1 + cp_1;
    double vp_2 = vm_2 + cp_2;

    // half-step electric field update: this gives final particle velocity
    pList[pIdx].v[0] = vp_0 - qmdt*E_0;
    pList[pIdx].v[1] = vp_1 - qmdt*E_1;
    pList[pIdx].v[2] = vp_2 - qmdt*E_2;

    // update particle position
    pList[pIdx].x[0] = pList[pIdx].x[0] + dt*pList[pIdx].v[0];
    pList[pIdx].x[1] = pList[pIdx].x[1] + dt*pList[pIdx].v[1];
    pList[pIdx].x[2] = pList[pIdx].x[2] + dt*pList[pIdx].v[2];

    count = count + 1;
  }

  return count;
}

int
main (void) {
  double E[3], B[3];
  E[0] = E[1] = E[2] = 0.0;
  B[0] = B[1] = B[2] = 0.0;
  B[2] = 1.0;

  double q = 1.0, qbym = 1.0, dt = qbym/4.0;
  unsigned npart = 10000;
  std::vector<particle_t> pList(npart);
  
  for (unsigned i=0; i<npart; ++i)
  {
    pList[i].x[0] = 1.0;
    pList[i].x[1] = 0.0;
    pList[i].x[2] = 0.0;
    pList[i].v[0] = 0.0;
    pList[i].v[1] = 1.0;
    pList[i].v[2] = 0.0;  
  }

  unsigned count = 0;
  unsigned ntries = 10000;

  clock_t t1 = std::clock();
  for (unsigned t=0; t<ntries; ++t)
  {
    count += borisPush(1.0, 1.0, dt, E, B, pList);
  }
  clock_t t2 = std::clock();
  std::cout << "Total particle updates " << count/1e6 << " million in " << (double) (t2-t1)/CLOCKS_PER_SEC << std::endl;
  
  return 0;
}
