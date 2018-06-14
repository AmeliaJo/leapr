#define CATCH_CONFIG_MAIN
#include "coh/coh_util/sigcoh.h"


TEST_CASE( "sigcoh" ){
  int k = 0;
  std::vector<double> p(6);
  double scon;
  GIVEN( "input energy is 0" ){
    std::vector<double> wrk_1_100 (100), s (6, 0.0), fl {};
    double e = 0, enext = 0, temp = 296, emax;
    int nl = 1, lat = 1, natom = 1;

    wrk_1_100 = { 8.79447930e15, 0.00000000000, 8.79447930e15, 0.00000000000, 
      3.5177917e16, 2.0984634e-8, 3.5177917e16, 2.0984634e-8, 7.9150313e16,
      0.0000000000, 7.9150313e16, 0.0000000000, 8.7173024e16, 1.6269500e-9, 
      8.7173024e16, 1.6269500e-9, 8.7173024e16, 1.6269500e-9, 9.5967503e16, 
      9.2661335e-9, 9.5967503e16, 9.2661335e-9, 9.5967503e16, 9.2661335e-9, 
      1.2235094e17, 2.7025149e-9, 1.2235094e17, 2.7025149e-9, 1.2235094e17, 
      2.7025149e-9, 1.4071166e17, 9.9954151e-9, 1.4071166e17, 9.9954151e-9, 
      1.6632333e17, 6.8145472e-9, 1.6632333e17, 6.8145472e-9, 1.6632333e17, 
      6.8145472e-9, 2.1986198e17, 0.0000000000, 2.1986198e17, 0.0000000000, 
      2.2788469e17, 1.8864426e-9, 2.2788469e17, 1.8864426e-9, 2.2788469e17, 
      1.8864426e-9, 2.6151907e17, 1.3871522e-8, 2.6151907e17, 2.7743045e-8, 
      2.7031355e17, 0.0000000000, 2.7031355e17, 1.418678e-37, 2.9669698e17, 
      2.5628649e-8, 2.9669698e17, 5.1257299e-8, 3.0703500e17, 4.7013822e-9, 
      3.0703500e17, 4.7013822e-9, 3.0703500e17, 4.7013822e-9, 3.1660125e17, 
      6.1459915e-9, 3.1660125e17, 6.1459915e-9, 3.4066938e17, 0.0000000000, 
      3.4066938e17, 1.223500e-37, 3.4869209e17, 7.213234e-10, 3.4869209e17, 
      7.213234e-10, 3.4869209e17, 7.213234e-10, 3.5748657e17, 4.2571271e-9, 
      3.5748657e17, 4.2571271e-9, 3.5748657e17, 4.2571271e-9, 3.8387001e17, 
      1.3528993e-9, 3.8387001e17, 1.3528993e-9, 3.8387001e17, 1.3528993e-9, 
      4.0223074e17, 4.1937649e-8, 4.0223074e17, 2.0968824e-8, 4.0377427e17, 
      1.3071163e-9 }; 
  
  
   
    WHEN( "smal value for emax" ){
      emax = 0.05;
      THEN ( "loops ranges are small (~4)" ){
       auto wrk = sigcoh( e, enext, s, nl, lat, temp, emax, natom, fl, p, k, scon );
        for ( size_t i = 0; i < 100; ++i ){ 
          REQUIRE( wrk_1_100[i] == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
        std::vector<double> wrk_200_265( 65);
        wrk_200_265 = { 2.3742272e-9, 7.8455721e17, 6.2970216e-9, 7.8455721e17, 
          6.2970216e-9, 7.8455721e17, 6.2970216e-9, 7.9335169e17, 3.255566e-38, 
          7.9335169e17, 3.255566e-38, 7.9335169e17, 1.302226e-37, 7.9952584e17, 
          2.3231321e-9, 7.9952584e17, 2.3231321e-9, 7.9952584e17, 2.3231321e-9, 
          8.1973513e17, 1.2123197e-8, 8.1973513e17, 1.2123197e-8, 8.1973513e17, 
          1.2123197e-8, 8.2436574e17, 2.4126785e-8, 8.2436574e17, 1.2063392e-8, 
          8.3007315e17, 4.4963798e-9, 8.3007315e17, 4.4963798e-9, 8.3007315e17, 
          4.4963798e-9, 8.6370753e17, 3.020849e-38, 8.6370753e17, 3.020849e-38, 
          8.6370753e17, 1.208339e-37, 8.7944793e17, 2.8468646e-9, 8.7944793e17, 
          2.8468646e-9, 9.1153877e17, 6.888381e-10, 9.1153877e17, 6.888381e-10, 
          9.1153877e17, 6.888381e-10, 9.2526888e17, 1.0870497e-8, 9.2526888e17, 
          1.0870497e-8, 9.2526888e17, 1.0870497e-8, 9.2681242e17, 1.3567171e-9, 
          9.2681242e17, 1.3567171e-9, 9.2681242e17, 1.3567171e-9, 9.6519234e17, 
          1.3567171e-9, 0.00000000000 }; 
        for ( size_t i = 0; i < 65; ++i ){ 
          REQUIRE( wrk_200_265[i] == Approx( wrk[199+i] ).epsilon(1e-6) );
        }
 
        for ( int i = 264; i < wrk.size(); ++i ){ 
          REQUIRE( 0.0 == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
      } // THEN 
    } // WHEN

  
    WHEN( "Medium value for emax" ){
      emax = 1.2;
      THEN ( "loops ranges are moderate (~17)" ){
       auto wrk = sigcoh( e, enext, s, nl, lat, temp, emax, natom, fl, p, k, scon );

        for ( size_t i = 0; i < 100; ++i ){ 
          REQUIRE( wrk_1_100[i] == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
        std::vector<double> wrk_500_600 (100);
        wrk_500_600 = { 2.374077e-09, 1.1973575e19, 7.053895e-12, 1.1974813e19, 
          1.105192e-38, 1.1990248e19, 2.080840e-10, 1.2039642e19, 1.757036e-09, 
          1.2649853e19, 6.497581e-11, 1.2693627e19, 3.936175e-11, 1.2699228e19, 
          1.533214e-09, 1.3351059e19, 1.063848e-11, 1.3369581e19, 5.270483e-12, 
          1.3376403e19, 1.163428e-09, 1.4052159e19, 4.006684e-11, 1.4065727e19, 
          1.243702e-12, 1.4071166e19, 7.846096e-10, 1.4783519e19, 6.588293e-10, 
          1.5543523e19, 9.596001e-12, 1.5555728e19, 2.980286e-12, 1.5568076e19, 
          1.059922e-11, 1.5600634e19, 3.722768e-10, 1.6260992e19, 3.579090e-10, 
          1.7085912e19, 2.417811e-11, 1.7113284e19, 2.177208e-10, 1.7808820e19, 
          1.643088e-10, 1.8701836e19, 7.680230e-13, 1.8705982e19, 2.567755e-11, 
          1.8809630e19, 9.866590e-12, 1.8883720e19, 7.926673e-12, 1.8955476e19, 
          5.656563e-13, 1.8957810e19, 5.909501e-11, 1.9427004e19, 9.376579e-11, 
          2.0402813e19, 6.728049e-13, 2.0425859e19, 2.106142e-12, 2.0434797e19, 
          1.104108e-13, 2.0437417e19, 1.124968e-11, 2.0532470e19, 2.994409e-12, 
          2.0611172e19, 3.199448e-11, 2.1115544e19, 4.634311e-11, 2.2174057e19, 
          8.926069e-41, 2.2178258e19, 9.496831e-13, 2.2207100e19, 3.700054e-13, 
          2.2247717e19, 1.500625e-12, 2.2316294e19, 3.430352e-13, 2.2334890e19, 
          1.643782e-11, 2.2874440e19, 4.589983e-12, 2.3164615e19, 4.589983e-12, 
          0.0000000000, 0.0000000000, 0.0000000000, 0.0000000000, 0.0000000000, 
          0.0000000000, 0.0000000000, 0.0000000000, 0.0000000000, 0.0000000000, 
          0.0000000000, 0.0000000000 };
        for ( size_t i = 0; i < 100; ++i ){ 
          REQUIRE( wrk_500_600[i] == Approx( wrk[499+i] ).epsilon(1e-6) );
        }
        for ( int i = 599; i < wrk.size(); ++i ){ 
          REQUIRE( 0.0 == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
      } // THEN 
    } // WHEN
    WHEN( "large value for emax" ){
      emax = 5.5;
      THEN ( "loops ranges are large (~35)" ){
       auto wrk = sigcoh( e, enext, s, nl, lat, temp, emax, natom, fl, p, k, scon );
  

        for ( size_t i = 0; i < 100; ++i ){ 
          REQUIRE( wrk_1_100[i] == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
        std::vector<double> wrk_500_600 (100);

        wrk_500_600 = { 2.374077e-09, 1.1973575e19, 7.053895e-12, 1.1974813e19, 
          1.105192e-38, 1.1990248e19, 2.080840e-10, 1.2039642e19, 1.757036e-09, 
          1.2649853e19, 6.497581e-11, 1.2693627e19, 3.936175e-11, 1.2699228e19, 
          1.533214e-09, 1.3351059e19, 1.063848e-11, 1.3369581e19, 5.270483e-12, 
          1.3376403e19, 1.163428e-09, 1.4052159e19, 4.006684e-11, 1.4065727e19, 
          1.243702e-12, 1.4071166e19, 7.846096e-10, 1.4783519e19, 6.588293e-10, 
          1.5543523e19, 9.596001e-12, 1.5555728e19, 2.980286e-12, 1.5568076e19, 
          1.059922e-11, 1.5600634e19, 3.722768e-10, 1.6260992e19, 3.579090e-10, 
          1.7085912e19, 2.417811e-11, 1.7113284e19, 2.177208e-10, 1.7808820e19, 
          1.643088e-10, 1.8701836e19, 7.680230e-13, 1.8705982e19, 2.567755e-11, 
          1.8809630e19, 9.866590e-12, 1.8883720e19, 7.926673e-12, 1.8955476e19, 
          5.656563e-13, 1.8957810e19, 5.909501e-11, 1.9427004e19, 9.376579e-11, 
          2.0402813e19, 6.728049e-13, 2.0425859e19, 2.106142e-12, 2.0434797e19, 
          1.104108e-13, 2.0437417e19, 1.124968e-11, 2.0532470e19, 2.994409e-12, 
          2.0611172e19, 3.199448e-11, 2.1115544e19, 4.634311e-11, 2.2174057e19, 
          8.926069e-41, 2.2178258e19, 9.496831e-13, 2.2207100e19, 3.700054e-13, 
          2.2247717e19, 1.500625e-12, 2.2316294e19, 3.430352e-13, 2.2334890e19, 
          1.643782e-11, 2.2874440e19, 1.875968e-11, 2.4032456e19, 1.558079e-13, 
          2.4040012e19, 5.286093e-13, 2.4087126e19, 1.127789e-12, 2.4128964e19, 
          7.573101e-12, 2.4703692e19, 9.766221e-12, 2.5944735e19, 7.781686e-15, 
          2.5959597e19, 1.259472e-13 };
        for ( size_t i = 0; i < 100; ++i ){ 
          REQUIRE( wrk_500_600[i] == Approx( wrk[499+i] ).epsilon(1e-6) );
        }


        std::vector<double> wrk_800_870( 70 );
        wrk_800_870 = { 6.601181e-23, 8.1049921e19, 1.073950e-22, 8.5106395e19, 
          1.986954e-26, 8.5107596e19, 1.059116e-25, 8.5108335e19, 3.965235e-26, 
          8.5115244e19, 2.638132e-26, 8.5116950e19, 4.752281e-25, 8.5190360e19, 
          2.351705e-25, 8.5246736e19, 6.748687e-24, 8.6194691e19, 1.044494e-23, 
          9.0505271e19, 1.610302e-27, 9.0505327e19, 8.925221e-26, 9.0585771e19, 
          1.107440e-26, 9.0603545e19, 1.071331e-25, 9.0795695e19, 1.764720e-25, 
          9.1083021e19, 1.063533e-26, 9.1107251e19, 2.068434e-25, 9.1497762e19, 
          9.109218e-25, 9.6074437e19, 1.207860e-28, 9.6076114e19, 2.812761e-28, 
          9.6085639e19, 4.282994e-27, 9.6143882e19, 7.052932e-27, 9.6348507e19, 
          3.188715e-27, 9.6428286e19, 1.533340e-28, 9.6438859e19, 3.135256e-27, 
          9.6515856e19, 1.975937e-26, 9.6959134e19, 7.590059e-26, 1.0180907e20, 
          8.403625e-30, 1.0180961e20, 4.195250e-30, 1.0182124e20, 8.356230e-30, 
          1.0182629e20, 2.058866e-28, 1.0185788e20, 3.267650e-28, 1.0195299e20, 
          6.164371e-28, 1.0208276e20, 1.541683e-27, 1.0257880e20, 5.068201e-27, 
          1.0617115e20, 5.068201e-27 };
        for ( size_t i = 0; i < 70; ++i ){ 
          REQUIRE( wrk_800_870[i] == Approx( wrk[799+i] ).epsilon(1e-6) );
        }

        for ( int i = 869; i < wrk.size(); ++i ){ 
          REQUIRE( 0.0 == Approx( wrk[i] ).epsilon(1e-6) );
        }
  
      } // THEN 
    } // WHEN
  } // GIVEN

  GIVEN( "input energy is greater than 0" ){
    double e = 1.822326e-3, enext = 1.822326e-3, temp = 296.0, emax = 1.2;
    std::vector<double> s (10, 0.0), fl (588);
    int nl = 1, lat = 1, natom = 1, k = 294;
    for ( int i = 0; i < 588; ++i ){ fl[i] = i + 1; }
    scon = 321038.24532333424;
    p[0] = 1.0; p[1] = -1.0;

    auto wrk = sigcoh( e, enext, s, nl, lat, temp, emax, natom, fl, p, k, scon );



  } // GIVEN

} // TEST CASE