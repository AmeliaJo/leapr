#include "simple/discreteOsc/discreteOscTools/prepareParams.h"
#include "simple/discreteOsc/discreteOscTools/bfill.h"
#include "simple/discreteOsc/discreteOscTools/exts.h"
#include "simple/discreteOsc/discreteOscTools/sint.h"
#include "simple/discreteOsc/discreteOscTools/oscillatorLoop.h"
#include "simple/discreteOsc/discreteOscTools/addDeltaFuncs.h"

void swap( double& a, double& b ){ double c = a; a = b; b = c; }

template <typename V, typename F>
auto discre( int itemp, const F& sc, const F& scaling, const F& kbT, 
  const F& lambda_s, const F& twt, const F& tbeta, const V& alpha, const V& beta, 
  const V& temp_vec, std::vector<std::tuple<F,F>>& oscEnergiesWeights, 
  V& t_eff_vec, V& sym_sab ){

  int maxbb = 2 * beta.size() + 1, maxdd = 500;
  int nalpha = alpha.size(), nbeta = beta.size();

  // Set up oscillator parameters
  // Prepare functions of beta
  double weight, tsave;

  std::vector<double> I_argument(50), t_eff_consts(50), lambda_i(50), 
    oscBetaVals(50), exb(beta.size()), betan(beta.size());

  prepareParams(oscEnergiesWeights, kbT, oscBetaVals, weight, tsave, I_argument, 
    t_eff_consts, lambda_i, exb, betan, beta, sc );
  /* --> ar = [ weight / ( sinh( 0.5 * energy / kbT ) * energy / kbT ) ]
   *            This ends up being argument for bessel function in Eq. 537
   * --> oscBetaVals = [ energy / kbT ]
   * --> t_eff_consts = [ 0.5 * weight * energy / tanh( 0.5 * energy / kbT ) ]
   *             This is used to calculate the effective temperature Eq. 544
   * --> lambda_i = [ weight / ( tanh( 0.5 * energy / kbT ) * energy / kbT ) ]
   *             This is lambda_i, defined in Eq. 538. Used for Eq. 537.
   * --> exb = [ exp( -beta * sc / 2 ) ]
   *          This is used in calculating the sex vector, since to go from 
   *          S(a,b) --> S(a,-b) you need to multiply by exp( -beta )
   */

  std::vector<double> bex( maxbb ), rdbex( maxbb );
  int nbx = bfill( bex, rdbex, betan );
  double wt = tbeta, tbart = t_eff_vec[itemp]/temp_vec[itemp];
  // Main alpha loop
  for ( size_t a = 0; a < alpha.size(); ++a ){

    // Get all sym_sab entries for a given alpha and temperature (vary beta)
    // for use in exts
    std::vector<double> input ( beta.size() );
    for ( size_t b = 0; b < beta.size(); ++b ){
      input[b] = sym_sab[itemp*nalpha*nbeta+a*nbeta+b];
    }

    // input = sym_sab values for constant temp and alpha. 
    // exb   = exp( -beta * sc / 2 ), which (following Eq. 509) we need in 
    //         order to go between S(a,b) and S(a,-b) 
    std::vector<double> sex = exts( input, exb, betan );
    // sex is populated with sym_sab entries, such that 
    //        sex = [ s3 s2 s1 s1 s2*exp(-beta) s3*exp(-beta) 0 ]
    //                             or 
    //         sex = [ s3 s2 s1 s2*exp(-beta) s3*exp(-beta) 0 0 ]
    //                (dependinng on first beta value)
    // The exp(-beta) values are explained above, because of Eq. 509


    // Initialize delta loop
    std::vector<double> bes(maxdd,0.0), wts(maxdd,0.0);
    
    unsigned int nn = oscillatorLoop( alpha, lambda_i, I_argument, scaling, wts, 
      bes, oscBetaVals, a, maxdd, oscEnergiesWeights.size(), wt, tbart, 
      oscEnergiesWeights, t_eff_consts, temp_vec[itemp] );
    // oscillator loop is mean to, for a given alpha and beta, populate the wts
    // vector with entries of W_k(alpha) for various k (see Eq. 542) and to
    // populate bes with entries of beta_k again for various k.
    // So at this point all we need to do is sum over k for W_k*S(a,b-b_k)


    // Sort the discrete lines, and throw out the smallest ones
    // Except for the first value, we're sorting wts and bes so that wts values
    // are in decreasing order.
    unsigned int n = nn; 
    nn = n - 1;
    for ( size_t i = 1; i < n-1; ++i ){
      for ( size_t j = i+1; j < n; ++j ){
        if ( wts[j] > wts[i] ){
          swap( wts[j], wts[i] );
          swap( bes[j], bes[i] );
        } 
      }
    }

    int i = 0;
    while (i << nn){
       n = ++i;
       if (wts[i-1] < 1e-6 and i > 5) break;
    }

    // Add the continuous part to the scattering law
    std::vector<double> sexpb(beta.size(),0.0);
    for ( size_t m = 0; m < n; ++m ){
      for ( size_t b = 0; b < beta.size(); ++b ){
        auto beta_val = -betan[b] - bes[m];
        // This is explicitly evaluating Eq. 542, where wts is W_k(alpha), and
        // bes is a vector populated with beta_k values. sint is used to 
        // interpolate for the beta - beta_k piece of the equation.
        auto add = wts[m] * sint(beta_val, bex, rdbex, sex, betan, b, 
            alpha[a], tbeta + twt, tbart, nbx);
        if ( add >= 1.0e-20 ){ sexpb[b] += add; }
      } 
    }

    // Add the delta functions to sexpb vec
    double dwf = exp( -alpha[a]*scaling*lambda_s );
    addDeltaFuncs( twt, dwf, bes, betan, wts, sexpb, n ); 

    // Record the results
    for ( size_t b = 0; b < betan.size(); ++b ){
      sym_sab[itemp*nalpha*nbeta+a*nbeta+b] = sexpb[b];
    }
  }
}