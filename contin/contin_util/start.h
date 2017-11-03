#include <vector>
#include <tuple>
#include <cmath>
#include <iostream>
#include "start_util/start_util.h"

double start( std::vector<double>& p, double& delta, const double& tev, 
  const double& tbeta ){
  // start makes delta unitless, changing it to what leapr.f90 calls deltab
  
  delta = delta / tev; // make delta is unitless

  // Move phonon distribution rho(beta) to P(beta) by discretely solving at 
  // points delta apart. This follows Eq. 507
  double beta = delta;
  double exp_val_0 = std::exp(delta/2);
  double exp_increment = exp_val_0;
  
  p[0] = p[1] / (std::pow(delta,2));
  for ( int i = 1; i < p.size(); ++i ){
    p[i] = p[i] / ( beta * ( exp_increment - std::pow(exp_increment, -1) ) );
    // increment values for next iteration
    beta += delta; exp_increment *= exp_val_0;
  }

  // normalize p so now it integrates to tbeta
  normalize( p, delta, tbeta );

  // calculate debye-waller coefficient and effective temperature
  double lambda_s = fsum( 0, p, 0.5, delta );
  double t_eff    = fsum( 2, p, 0.5, delta ) / ( 2 * tbeta );

  // convert p(beta) --> t1(beta) where t1 is defined to be
  // t1( beta ) = p( beta ) * exp( -beta / 2 ) / lambda_s where
  // lamda_s is the debye-waller coefficient. This relationship
  // is defined by Eq. 525.
  for ( int i = 0; i < p.size(); ++i ){
   p[i] = p[i] * exp( delta * i / 2 ) / lambda_s;
  }
  return lambda_s;
}


