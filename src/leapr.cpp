#include "continuous/continuous.h"
#include "translational/translational.h"
#include "discreteOscillators/discreteOscillators.h"
#include "coldHydrogen/coldHydrogen.h"
#include "coherentElastic/coherentElastic.h"
#include "skold/skold.h"
#include "generalTools/constants.h"
#include <range/v3/all.hpp>
#include <variant>
#include "endout/endout.h"
using namespace njoy;
#include "lipservice.hpp"


auto finalLEAPR( nlohmann::json jsonInput ){

  int nphon = jsonInput["nphon"];

  // Do we have a secondary scatterer?
  int numSecondaryScatterers = jsonInput["nss"];
  int b7 = 0;
  if (numSecondaryScatterers > 0){ b7 = jsonInput["b7"]; }
  int numIter = 2;
  if ( numSecondaryScatterers == 0 or b7 > 0 ){ numIter = 1; }


  int    lat = jsonInput["lat"];
  double awr = jsonInput["awr"];
  double aws = 0.0;
  if (numSecondaryScatterers > 0){ aws = jsonInput["aws"]; }
  //double aws = jsonInput["aws"];

  auto temperatureInfo = jsonInput["temperatures"];
  std::vector<double> dwpix (temperatureInfo.size(),0.0),
                      tempf (temperatureInfo.size(),0.0),
                      dwp1  (temperatureInfo.size(),0.0),
                      tempf1(temperatureInfo.size(),0.0);

  int ncold = jsonInput["ncold"];
  int isabt = jsonInput["isabt"];

  std::vector<double> alphas = jsonInput["alpha"];
  std::vector<double> betas  = jsonInput["beta"];

  std::vector<std::vector<double>> sab_AllTemps(temperatureInfo.size());
  std::vector<double> temperatures(temperatureInfo.size());
  for (int scatterIter = 0; scatterIter < numIter; ++scatterIter){

    for (size_t itemp = 0; itemp < temperatureInfo.size(); ++itemp){

      auto tempInfo = temperatureInfo[itemp];

      double temperature = tempInfo["temperature"];
      if (scatterIter == 0){ temperatures[itemp] = temperature; }

      std::vector<double> sab(alphas.size()*betas.size(),0.0);
      std::vector<double> sab2(alphas.size()*betas.size(),0.0);
      double tev = kb * temperature;

      double sc   = (lat         == 1) ? 0.0253/tev : 1.0,
             arat = (scatterIter == 0) ?        1.0 : aws/awr;
      double scaling = sc/arat;
      std::vector<double> scaledAlphas = alphas,
                          scaledBetas  = betas;
      for ( double& a : scaledAlphas ){ a *= scaling; }
      for ( double& b : scaledBetas  ){ b *= sc;      }


      //---------------- Incoherent (Elastic and Inelastic) ----------------------
      double rho_dx           = tempInfo["delta"];
      rho_dx /= tev;
      double continuousWgt    = tempInfo["tbeta"];
      std::vector<double> rho = tempInfo["rho"];
      auto continOutput  = continuous(nphon, rho_dx, continuousWgt, rho, 
                                      scaledAlphas, scaledBetas, sab);
      dwpix[itemp] = std::get<0>(continOutput);
      tempf[itemp] = std::get<1>(continOutput)*temperature;
    
      double transWgt = tempInfo["twt"];
      if (transWgt > 0){
        double diffusion_const = tempInfo["c"];
        translational( scaledAlphas, scaledBetas, transWgt, rho_dx, diffusion_const, 
               dwpix[itemp], continuousWgt, tempf[itemp], temperature, sab );
      }

      if (not tempInfo["oscillators"]["energies"].is_null()){
        std::vector<double> oscillatorEnergies = tempInfo["oscillators"]["energies"];
        std::vector<double> oscillatorWeights  = tempInfo["oscillators"]["weights"];
        auto oscEnergiesWgts = ranges::view::zip(oscillatorEnergies,oscillatorWeights);
        discreteOscillators( dwpix[itemp], transWgt, continuousWgt, scaledAlphas, 
                             scaledBetas, temperature, oscEnergiesWgts, 
                             tempf[itemp], sab );
      }

      if (ncold > 0){
        bool free = false;
        auto pairCorrelationInfo = tempInfo["pairCorrelation"];
        std::vector<double> kappa = pairCorrelationInfo["skappa"];
        double                dka = pairCorrelationInfo["dka"];
        coldHydrogen( tev, ncold, transWgt+continuousWgt, alphas, betas, dka, 
                      kappa, free, sab, sab2, tempf[itemp]);
      }

      sab_AllTemps[itemp] = sab;

    } // temp loop

    if (scatterIter == 0 and numIter == 2){
      for (size_t itemp = 0; itemp < temperatureInfo.size(); ++itemp){
        tempf1[itemp] = tempf[itemp];
        dwp1[itemp]   = dwpix[itemp];
      }
    }

  } // Primary and Secondary Scatter Loop
  

  //---------------- Coherent (Elastic) ----------------------
  int iel = jsonInput["iel"];
  unsigned int npr = jsonInput["npr"];
  std::variant<std::vector<double>,bool> braggOutput;
  std::vector<double> bragg ( 60000, 0.0 );
  int nedge = 0;
  if (iel > 0){
    double emax = 5.0;
    auto coherentElasticOut = coherentElastic( iel, npr, bragg, emax );
    nedge = std::get<1>(coherentElasticOut)* 0.5;
    bragg.resize(std::get<0>(coherentElasticOut)); 
    braggOutput = bragg;
  }
  else { 
      braggOutput = false; 
      bragg.resize(0);
  }
  //int numEdges = bragg.size();

  //---------------------------- Write Output --------------------------------

  int za = jsonInput["za"];
  std::vector<double> awrVec {awr,aws};
  if (numSecondaryScatterers == 0){ awrVec.resize(1); }

  double spr = jsonInput["spr"];
  double sps = 0.0;
  if (numSecondaryScatterers > 0){ sps = jsonInput["sps"]; }
  
  int ilog = jsonInput["ilog"];

  int isym = 0;
  if (ncold != 0){ isym = 1; }
  if (isabt == 1){ isym += 2; }

  double transWgt = temperatureInfo[temperatures.size()-1]["twt"];

  std::vector<unsigned int> numAtomsVec;
  if (numSecondaryScatterers == 0){ numAtomsVec = {npr}; }
  else { numAtomsVec = {npr,jsonInput["mss"]}; }

    njoy::ENDFtk::file::Type<7> MF7 = endout(sab_AllTemps,za,awrVec,spr,sps,temperatures,
          numSecondaryScatterers, b7 , sab_AllTemps,alphas,
          betas,dwpix,dwp1,iel,transWgt,bragg,nedge,tempf,tempf1,ilog,
          isym,lat,numAtomsVec);

  return MF7;

}























/*



template <typename Range, typename RangeOfRanges, typename Float>
auto leapr( std::vector<int> generalInfo, std::vector<int> scatterControl,
  Range scatterInfo, Range temps, Range alphas, Range betas, RangeOfRanges rhoVec, 
  Range rho_dx_vec, RangeOfRanges transInfo, RangeOfRanges oscE_vec, 
  RangeOfRanges oscW_vec, Float smin, std::tuple<std::vector<double>,double> 
  kappaInfo = std::tuple<std::vector<double>,double>() ){

  int nphon = generalInfo[0];

  // Do we have a secondary scatterer?
  int numSecondaryScatterers = scatterControl[4],
                          b7 = scatterControl[5];
  int numIter = 2;
  if ( numSecondaryScatterers == 0 or b7 > 0 ){ numIter = 1; }


  int  lat = generalInfo[5];
  auto awr = scatterInfo[0];
  auto aws = scatterInfo[2];

  Range dwpix (temps.size(),0.0),
        tempf (temps.size(),0.0),
        dwp1  (temps.size(),0.0),
        tempf1(temps.size(),0.0);

  int ncold = scatterControl[2];
  int isabt = generalInfo[3];

  std::vector<std::vector<Float>> sab_AllTemps(temps.size());
  for (int scatterIter = 0; scatterIter < numIter; ++scatterIter){

    for (size_t itemp = 0; itemp < temps.size(); ++itemp){

      std::vector<Float> sab(alphas.size()*betas.size(),0.0);
      std::vector<Float> sab2(alphas.size()*betas.size(),0.0);
      auto tev = kb * temps[itemp];

      Float sc   = (lat         == 1) ? 0.0253/tev : 1.0,
            arat = (scatterIter == 0) ?        1.0 : aws/awr;
      Float scaling = sc/arat;
      Range scaledAlphas = alphas,
            scaledBetas  = betas;
      for ( auto& a : scaledAlphas ){ a *= scaling; }
      for ( auto& b : scaledBetas  ){ b *= sc;      }


      //---------------- Incoherent (Elastic and Inelastic) ----------------------
      auto rho_dx        = rho_dx_vec[itemp]/tev;
      auto continuousWgt = transInfo[2][itemp];
      auto rho           = rhoVec[itemp];
      auto continOutput  = continuous(nphon, rho_dx, continuousWgt, rho, 
                                      scaledAlphas, scaledBetas, sab);
      dwpix[itemp] = std::get<0>(continOutput);
      tempf[itemp] = std::get<1>(continOutput)*temps[itemp];
    
      auto transWgt = transInfo[0][itemp];
      if (transWgt > 0){
        auto diffusion_const = transInfo[1][itemp];
        translational( scaledAlphas, scaledBetas, transWgt, rho_dx, diffusion_const, 
               dwpix[itemp], continuousWgt, tempf[itemp], temps[itemp], sab );
      }

      auto oscEnergiesWgts = ranges::view::zip(oscE_vec[itemp],oscW_vec[itemp]);
      if (oscEnergiesWgts.size() > 0){
        discreteOscillators( dwpix[itemp], transWgt, continuousWgt, scaledAlphas, scaledBetas, 
                temps[itemp], oscEnergiesWgts, tempf[itemp], sab );
      }

      if (ncold > 0){
        bool free = false;

        std::vector<double> kappa = std::get<0>(kappaInfo);
        double dka                = std::get<1>(kappaInfo);
        coldHydrogen( tev, ncold, transWgt+continuousWgt, alphas, betas, dka, kappa, free, 
               sab, sab2, tempf[itemp]);
      }

      sab_AllTemps[itemp] = sab;

    } // temp loop

    if (scatterIter == 0 and numIter == 2){
      for (size_t itemp = 0; itemp < temps.size(); ++itemp){
        tempf1[itemp] = tempf[itemp];
        dwp1[itemp]   = dwpix[itemp];
      }
    }

  } // Primary and Secondary Scatter Loop
  

  //---------------- Coherent (Elastic) ----------------------
  int iel = scatterControl[1];
  unsigned int npr = scatterControl[0];
  std::variant<Range,bool> braggOutput;
  std::vector<double> bragg ( 60000, 0.0 );
  int nedge = 0;
  if (iel > 0){
    double emax = 5.0;
    auto coherentElasticOut = coherentElastic( iel, npr, bragg, emax );
    nedge = std::get<1>(coherentElasticOut)* 0.5;
    bragg.resize(std::get<0>(coherentElasticOut)); 
    braggOutput = bragg;
  }
  else { 
      braggOutput = false; 
      bragg.resize(0);
  }

  //---------------------------- Write Output --------------------------------

  int za = generalInfo[2];
  std::vector<Float> awrVec {awr,aws};
  if (numSecondaryScatterers == 0){ awrVec.resize(1); }

  Float spr = scatterInfo[1],
        sps = scatterInfo[3];
  
  int ilog = generalInfo[4];


  int isym = 0;
  if (ncold != 0){ isym = 1; }
  if (isabt == 1){ isym += 2; }


  auto transWgt = transInfo[0][temps.size()-1];
  unsigned int mss = scatterControl[6];
  std::vector<unsigned int> numAtomsVec {npr,mss};
  if (numSecondaryScatterers == 0){ numAtomsVec.resize(1); }

    njoy::ENDFtk::file::Type<7> MF7 = endout(sab_AllTemps,za,awrVec,spr,sps,temps,
          numSecondaryScatterers, b7 , sab_AllTemps,alphas,
          betas,dwpix,dwp1,iel,transWgt,bragg,nedge,tempf,tempf1,ilog,
          isym,lat,numAtomsVec);

  return MF7;
  std::cout << smin << std::endl;

}

*/
