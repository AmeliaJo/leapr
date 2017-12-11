#include <iostream>
#include <vector>
#include "coldh_util/terpk.h"
#include "coldh_util/betaLoop.h"
#include "../discre/discre_util/bfill.h"
#include "../discre/discre_util/exts.h"


auto coldh( int itemp, const double& temp, double tev, double sc, int ncold,
    double trans_weight, double tbeta, const std::vector<double>& tempf,
    double scaling, 
    const std::vector<double>& alpha, const std::vector<double>& beta, 
    double& dka, std::vector<double>& ska, int nbeta, int lat, bool free, 
    std::vector<std::vector<std::vector<double>>>& sym_sab,
    std::vector<std::vector<std::vector<double>>>& sym_sab_2 ){
  /* Convolve current scattering law with discrete rotational modes for ortho
   * or para hydrogen / deuterium. The discrete modes are calculated using 
   * formulas of Young and Koppel for vibrational ground state with coding 
   * based on contributions from Robert (Grenoble) and Neef (Julich). The 
   * approach of using solid/diffusive modes with discrete rotations is based
   * on the work of Keinert and Sax. Note that the final S(a,b) is not 
   * symmetric in beta
   */

  double angst = 1.0e-8;
  double eV = 1.60217733e-12;    // This is weird, you say? Yes, it is. 1 ev
                                 // should, in normal society, be 1.602e-19 J,
                                 // but alas we're just going to multiply this
                                 // by 1e7 because this is njoy
  double mass_H = 1.6726231E-24; // Mass of H in grams
  double mass_D = 3.343568E-24;  // Mass of D in grams
  double hbar = 1.05457266e-27;  // You might be thinking this doesn't look
                                 // quite right. You'd be correct. It should 
                                 // be ...e-34 for hbar --> [J*s], but no we
                                 // have it in [1e-7 J * s] because that's a 
                                 // good idea

  int nbx, maxbb = 2 * beta.size() + 1;

  double de, x, mass_H2_D2, bp, scatLenC, scatLenI, wt, tbart, therm = 0.0253;

  std::vector<double> exb(maxbb, 0.0 ), betan(nbeta, 0.0 ), bex(maxbb, 0.0 ), 
    rdbex(maxbb, 0.0 );
 

  // Either Ortho Deuterium or Para Deuterium 
  if ( ncold > 2 ){
    de = 0.0074;
    mass_H2_D2 = 6.69E-24;    // Mass of D2 in grams
    bp = hbar * sqrt( 2 /( de*eV*mass_D ) ) / ( 2 * angst ); 
    scatLenC = 0.668;
    scatLenI = 0.403;
  } 
  // Either Ortho Hydrogen or Para Hydrogen
  else {
    de = 0.0147;
    mass_H2_D2 = 3.3465E-24;  // Mass of H2 in grams
    bp = hbar * sqrt( 2 /( de*eV*mass_H ) ) / ( 2 * angst );
    scatLenC = 0.356;
    scatLenI = 2.526;
  }

  x = de / tev;
  wt = trans_weight + tbeta;
  tbart = tempf[itemp] / temp;



  for ( auto a = 0; a < alpha.size(); ++a ){
    double al = alpha[a]*scaling;
    double waven = angst * sqrt( mass_H2_D2 * tev * eV * al ) / hbar;
    double y = bp * waven;
    double sk = terpk( ska, dka, waven );

    // spin-correlation factors
    double evenSumConst, oddSumConst;
    // -----------------------------------------------------------------------
    // Thie is meant to recreate the table on pg. 662 of the manual, where we
    // get the A (even) and B (odd) terms for the summation in Eq. 567.
    // -----------------------------------------------------------------------
    // Ortho Hydrogen
    if (ncold == 1){ 
      evenSumConst = scatLenI * scatLenI / 3;
      oddSumConst  = sk * scatLenC * scatLenC + 2 * scatLenI * scatLenI / 3;
    } 
    // Para Hydrogen
    else if ( ncold == 2 ){
      evenSumConst = scatLenC * scatLenC * sk;
      oddSumConst  = scatLenI * scatLenI;
    } 
    // Ortho Deuterium
    else if ( ncold == 3 ){
      evenSumConst = sk * scatLenC * scatLenC + 5 * scatLenI * scatLenI / 8;
      oddSumConst  = 3  * scatLenI * scatLenI / 8;
    } 
    // Para Deuterium
    else if ( ncold == 4){ 
      evenSumConst = 3  * scatLenI * scatLenI / 4;
      oddSumConst  = sk * scatLenC * scatLenC + scatLenI * scatLenI / 4;
    }

    // Both the ortho and para scattering laws (Eq. 567-568) are multiplied by
    // a (4*pi/sigma_b) term (where sigma_b is the characteristic bound cross
    // section, 
    //    sigma_b = 4*pi*(Incoh Scattering Len^2 + Coh Scattering Len^2 ).
    // So to account for the 4*pi/sigma_b term, we divide by 
    //          Incoh Scattering Len^2 + Coh Scattering Len^2
    evenSumConst /= scatLenI * scatLenI + scatLenC * scatLenC;
    oddSumConst  /= scatLenI * scatLenI + scatLenC * scatLenC;

    // prepare arrays for sint
    
   if (a == 0){ 
      for ( auto b = 0; b < nbeta; ++b ){
          double be=beta[b];
          if (lat == 1){ be = be * therm / tev; }
          exb[b] = exp(-be/2);
          betan[b] = be;
      } 
      nbx = bfill(bex,rdbex,betan);
    }
    std::vector<double> input ( beta.size(), 0.0 ); 
    for ( auto b = 0; b < beta.size(); ++b ){
      input[b] = sym_sab[a][b][itemp];
    }
    auto sex = exts( input, exb, betan );

    betaLoop( betan, rdbex, bex, sex, al, wt, tbart, x, y, evenSumConst, oddSumConst, itemp, 
       nbx, a, ncold, free, sym_sab, sym_sab_2 );

   
  }
 
}   