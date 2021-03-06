#include <iostream>
#include <vector>
//#include "hexLatticeFactors_util/hexLatticeFactorsHelper.h"
#include "coherentElastic/coherentElastic_util/formf.h" 
#include "generalTools/constants.h"



template <typename Range>
auto hexLatticeFactorsHelper( int& k, const double & tsq, const double& tsqx, 
  Range& b, const double& f ){
 
  if (k <= 0 or tsq <= tsqx) {
    k += 1;
    if (2*k > int(b.size())) { throw std::invalid_argument("2k must be <= b size"); } 
    b[2*k-2] = tsq;
    b[2*k-1] = f;
  }
  else {
    for ( int i = 1; i < k+1; ++i ){
      if ( tsq >= b[2*i-2] and tsq <= 1.05 * b[2*i-2] ) {
        b[2*i-1] += f;
	return;
      } // if
    } // while
    k++;
    b[2*k-2] = tsq;
    b[2*k-1] = f;
  } // else
}





// HEXAGONAL
template <typename Float>
Float tausq( int i1, int i2, int i3, const Float& c1, const Float& c2 ){
  /* This is meant to sort of evaluate Eq. 558. The output is  
   * multiplied by an extra factor of 2pi.
   * This is the reciprocal lattice vector length for hexagonal lattice 
   * (e.g. graphite). 
   */
  return (c1 * (i1*i1 + i2*i2 + i1*i2) + (i3*i3*c2)) * 4 * M_PI * M_PI;
}
// According to the HEXSCAT documentation, this actually calcualtes tau*tau
// because (tau/2pi)^2 = (4/3 a*a)(l1*l1 + l2*l2 + l1*l2) + l3*l3/(c*c)


template <typename Range>
int hexLatticeFactors( int lat, double a, double c, double maxTauSq, 
  Range& b ){

  using std::sqrt;

  int i2m, i3m, k = 0;
  double tau, f, tsq;
  // compute lattice factors for hexagonal lattices
  double phi = maxTauSq/(4*M_PI*M_PI), w1, w2, w3, 
              c1 = 4/(3*a*a), c2 = 1/(c*c), 
              tsqx = 8*massNeutron/(20*1e4*hbar*hbar)*ev;

  for ( auto i1 = 0; i1 < a*sqrt(phi); ++i1 ){
    i2m = int((i1+sqrt(3*(a*a*phi-i1*i1)))/2) + 1;

    for ( auto i2 = i1; i2 < i2m; ++i2 ){
      double x = phi-c1*(i1*i1+i2*i2-i1*i2);
      i3m = (x > 0) ? int(c*sqrt(x)) + 1 : 1;

      for ( auto i3 = 0; i3 < i3m; ++i3 ){
        w1 = (i1 == i2) ? 1 : 2;
        w3 = (i3 == 0)  ? 1 : 2;
        w2 = 2;
        if (i1 == 0 or  i2 == 0) w2 = 1;
        if (i1 == 0 and i2 == 0) w2 = w2/2;

        tsq = tausq(i1,i2,i3,c1,c2);

        if (tsq > 0 and tsq <= maxTauSq) {
          tau = sqrt(tsq);   // w1 w2 w3 are weighting factors
          //f = exp(-tsq*t2*wint)*w1*w2*w3/tau * formf(lat,i1,i2,i3);
          f =                     w1*w2*w3/tau * formf(lat,i1,i2,i3);
          hexLatticeFactorsHelper( k, tsq, tsqx, b, f );
        }

        tsq = tausq(i1,-i2,i3,c1,c2);

        if (tsq > 0 and tsq <= maxTauSq) {
          tau = sqrt(tsq);   // w1 w2 w3 are weighting factors
          //f = exp(-tsq*t2*wint)*w1*w2*w3/tau * formf(lat,i1,-i2,i3);
          f =                     w1*w2*w3/tau * formf(lat,i1,-i2,i3);
          hexLatticeFactorsHelper( k, tsq, tsqx, b, f );
        }

      } // 3

    } // 2

  } // 1

  return k-1; // This is imax

}


