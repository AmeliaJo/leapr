#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "continuous/continuous_util/convolution.h"

TEST_CASE( "convolution" ){
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 {0.2, 0.6, 0.8, 2.0, 6.0, 8.0},
      t2 {0.2, 0.6, 0.8, 2.0, 6.0, 8.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      output(18), correct(18); 
    double delta = 0.03;

    int nn = 18; 
    THEN( "the vectors are correctly convolved and result is returned" ){

      output = convolution( t1, t2, delta, nn ),
      correct = {3.8459762, 2.6993367, 1.0195307, 0.53364442, 0.37281623, 
        0.384, 0.624, 1.008, 1.8, 2.16, 0.96, 0, 0, 0, 0, 0, 0, 0};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
           
      t1 = {.01, .04, .09, .11, .16, .21};
      t2 = {.01, .04, .09, .11, .16, .21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

      delta = 0.5;
      output = convolution( t1, t2, delta, nn );
      correct = {1.1974704E-2, 1.3563056E-2, 1.3531928E-2, 1.379648E-2, 
        1.387114E-2, 1.7875E-2, 2.675E-2, 3.1775E-2, 3.0125E-2, 
        2.52E-2, 1.1025E-2, 0., 0., 0., 0., 0., 0., 0.};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
 
      t1 = {0.41483349, 0.49122347, 0.28793794, 0.19807373, 0.16013178, 
        0.35027406, 0.54943040};
      t2 = {0.41483349, 0.49122347, 0.28793794, 0.19807373, 0.16013178, 
        0.35027406, 0.5494304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      delta = 0.3481334;

      nn = 21; 
      output = convolution( t1, t2, delta, nn );
      correct = {0.24934471, 0.26630576, 0.25941571, 0.24935982, 0.26861886, 
        0.29515324, 0.28458452, 0.23324588, 0.1398470, 9.5883480E-2, 8.8657E-2,
        0.1004980, 5.2546179E-2, 0, 0, 0, 0, 0, 0, 0, 0};

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6 ) );  
      }
 
    } // THEN
  } // GIVEN
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 { 1.6145575501853762, 1.6966062728611888, 0.89067060932967568, 
         0.83055749019345759, 0.85698915228609684, 0.82062267112315690 },
      t2 { 1.6145575501853762, 1.6966062728611888, 0.89067060932967568, 
        0.83055749019345759, 0.85698915228609684, 0.82062267112315690, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0 },
    output(18), correct(18); 
    double delta = 9.9970755221739149e-2;
    int nn = 180; 

    THEN( "the vectors are correctly convolved and result is returned" ){

      output = convolution( t1, t2, delta, nn ),
      correct = { 1.152713, 1.1183255, 1.0309064, 0.923046, 0.826617, 0.637300, 
      0.430356, 0.251917, 0.175627, 0.105458, 3.366123e-2, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

      REQUIRE( output.size() == correct.size() );
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6) );  
      }
    } // THEN
  } // GIVEN
  GIVEN( "two vectors" ){
    std::vector<double> 
      t1 {1.041843, 1.0947883, 0.574733, 0.535943, 0.552999, 0.529532, 0.577232, 
          0.591247, 0.6148223, 0.643658 },
      t2 {0.466057, 0.4836946, 0.490538, 0.492844, 0.493187, 0.491510, 0.486330, 
          0.474123, 0.4512941, 0.416944, 0.375426, 0.335716, 0.300029, 0.267793, 
          0.235387, 0.2019125, 0.167430, 0.132371, 0.100639, 7.55876e-2, 
          5.77338e-2, 4.45148e-2, 3.300723e-2, 2.30710e-2, 1.46639e-2, 
          7.92340e-3, 3.18212e-3, 6.662738e-4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double delta = 9.9970755221739149e-2;
    int nn = 55;

    THEN( "the vectors are correctly convolved and result is returned" ){

      std::vector<double> output = convolution( t1, t2, delta, nn );
      std::vector<double> correct { 0.39224501, 0.4096017, 0.422550, 0.4315318, 
      0.437048, 0.439071, 0.437054, 0.430221, 0.417892, 0.400209, 0.378436, 
      0.354243, 0.328886, 0.302602, 0.275284, 0.246879, 0.217715, 0.188668, 
      0.160970, 0.135798, 0.113555, 9.39024E-2, 7.63567E-2, 6.06675E-2, 
      4.69068E-2, 3.52213E-2, 2.57685E-2, 1.85465E-2, 1.32286E-2, 9.29898E-3, 
      6.30190E-3, 4.00927E-3, 2.33081E-3, 1.18533E-3, 4.89892E-4, 1.43332E-4, 
      2.14363E-5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0 };
      for ( size_t i = 0; i < output.size(); ++i ){
        REQUIRE( output[i] == Approx( correct[i] ).epsilon(1e-6) );  
      }
    } // THEN
  } // GIVEN
} // TEST CASE


