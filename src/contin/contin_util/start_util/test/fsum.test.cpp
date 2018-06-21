#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "contin/contin_util/start_util/fsum.h"

void equalVec( const std::vector<double>& a, const std::vector<double>& b ){
  REQUIRE( a.size() == b.size() );
  for ( size_t i = 0; i < a.size(); ++i ){
    REQUIRE( b[i] == Approx( a[i] ).epsilon(1e-6 ) );  
  }
}



TEST_CASE( "fsum" ){
  std::vector<double> p1 {0.1, 0.2, 0.3, 0.4, 0.5, 0.6},
                      p2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  double tau, delta;

  WHEN( "n = 1 (used for normalizing p(beta)) " ){
    THEN( "returned value has as most a 1e-6 percent error" ){
      tau = 0.5, delta = 1.0;
      REQUIRE( fsum(1,p1,tau,delta) == Approx(39.387006).epsilon(1e-6) );

      delta = 2.0; tau = 0.5;
      REQUIRE( fsum(1,p2,tau,delta) == Approx(29610795.32).epsilon(1e-6));

    } // THEN
  } // WHEN
  for ( auto& entry : p1 ){ entry *= 0.1; }
  WHEN( "n = 0 (used for debye-waller coefficient) " ){
    THEN( "returned value has as most a 1e-6 percent error" ){
      tau = 0.5, delta = 0.1;
      REQUIRE( fsum(0,p1,tau,delta) == Approx(0.035514341).epsilon(1e-6) );

      delta = 2.0; tau = 0.5;
      REQUIRE( fsum(0,p2,tau,delta) == Approx(1444532.8400).epsilon(1e-6) );

    } // THEN
  } // WHEN
  WHEN( "n = 2 (used for effective temperature calculation) " ){
    THEN( "returned value has as most a 1e-6 percent error" ){
      tau = 0.5, delta = 0.7;
      REQUIRE( fsum(2,p1,tau,delta) == Approx(3.21945524).epsilon(1e-6) );

      delta = 2.0; tau = 0.5;
      REQUIRE( fsum(2,p2,tau,delta) == Approx(612298146.17046).epsilon(1e-6) );

    } // THEN
  } // WHEN
} // TEST CASE

