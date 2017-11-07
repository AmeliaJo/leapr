#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "sbfill.h"
#include <iostream>



void equal( double a, double b ){
    if( b == 0 ){ REQUIRE( (a-b) < 1e-6 ); }
    if( b != 0 ){ REQUIRE ( std::abs( (a-b)/(b) ) < 1e-6 ); }
}



TEST_CASE( "sbfill" ){
  GIVEN( "invalid inputs" ){
    int ndmax = 5100;
    std::vector<double> sb (ndmax,0.0); 
    std::vector<double> ap (ndmax,0.0); 
    for ( int i = 0; i < ap.size(); ++i ){
      ap[i] = (i+1)*0.0001;
    }
    std::vector<double> betan {0.15, 0.18, 0.22};
    int nbt = 2545;
    double delta = 1.791435E-3, be = 0.15;
    sbfill(sb, nbt, delta, be, ap, betan, ndmax );


    std::vector<double> correct {0.0, 0.0, 0.0, 0.0, 0.0, 2.995926E-4,
    2.942014E-4, 2.889072E-4, 2.837082E-4, 2.786028E-4, 2.735893E-4, 
    2.686660E-4, 2.638313E-4, 2.590836E-4, 2.544213E-4, 2.498429E-4, 
    2.453470E-4, 2.409319E-4, 2.365963E-4, 2.323387E-4, 2.281577E-4, 
    2.240519E-4, 2.200201E-4, 2.160607E-4, 2.121727E-4, 2.083546E-4, 
    2.046052E-4, 2.009233E-4, 1.939160E-4, 1.860534E-4, 1.785097E-4, 
    1.712719E-4, 1.643275E-4, 1.576646E-4, 1.512719E-4, 1.451385E-4, 
    1.392537E-4, 1.336075E-4, 1.281902E-4, 1.229926E-4, 1.180058E-4, 
    1.132211E-4, 1.086304E-4, 1.042259E-4, 9.999999E-5, 9.594539E-5, 
    9.205518E-5, 8.832271E-5, 8.474158E-5, 8.130564E-5, 7.800902E-5, 
    7.484606E-5, 7.181135E-5, 6.889969E-5, 6.610608E-5, 6.342574E-5, 
    6.085408E-5, 5.838669E-5, 5.601934E-5, 5.374798E-5, 5.156871E-5, 
    4.947780E-5, 4.747167E-5, 4.554688E-5, 4.370014E-5, 4.192827E-5, 
    4.022825E-5, 3.859715E-5, 3.703219E-5, 3.553068E-5, 3.409005E-5, 
    3.270784E-5, 3.138166E-5, 3.010926E-5, 2.888845E-5, 2.771714E-5, 
    2.659332E-5, 2.551506E-5, 2.448053E-5, 2.348794E-5, 2.253560E-5, 
    2.162187E-5, 2.074519E-5, 1.990405E-5, 1.909702E-5, 1.832271E-5, 
    1.757980E-5, 1.686701E-5, 1.618312E-5, 1.552696E-5, 1.489740E-5, 
    1.429337E-5, 1.371383E-5, 1.315779E-5, 1.262429E-5, 1.211243E-5, 
    1.162132E-5, 1.115012E-5, 1.069802E-5, 1.026426E-5, 9.848091E-6, 
    9.448790E-6, 9.065679E-6, 8.698101E-6, 8.345428E-6, 8.007054E-6, 
    7.682400E-6, 7.370909E-6, 7.072048E-6, 6.785304E-6, 6.510187E-6, 
    6.246225E-6, 5.992965E-6, 5.749974E-6, 5.516836E-6, 5.293150E-6, 
    5.078533E-6, 4.872619E-6, 4.675054E-6, 4.485499E-6, 4.303630E-6, 
    4.129135E-6, 3.961714E-6, 3.801083E-6, 3.646964E-6, 3.499094E-6, 
    3.357220E-6, 3.221098E-6, 3.158371E-6, 3.285950E-6, 3.418683E-6, 
    3.556778E-6, 3.700450E-6, 3.849926E-6, 4.005440E-6, 4.167236E-6, 
    4.335567E-6, 4.510698E-6, 4.692904E-6, 4.882469E-6, 5.079691E-6, 
    5.284881E-6, 5.498358E-6, 5.720459E-6, 5.951531E-6, 6.191938E-6, 
    6.442055E-6, 6.702275E-6, 6.973007E-6, 7.254675E-6, 7.547720E-6, 
    7.852603E-6, 8.169801E-6, 8.499812E-6, 8.843154E-6, 9.200365E-6, 
    9.572004E-6, 9.958656E-6, 1.036092E-5, 1.077944E-5, 1.121487E-5, 
    1.166788E-5, 1.213919E-5, 1.262954E-5, 1.313970E-5, 1.367047E-5, 
    1.422267E-5, 1.479718E-5, 1.539490E-5, 1.601676E-5, 1.666375E-5, 
    1.733686E-5, 1.803717E-5, 1.876576E-5, 1.952378E-5, 2.031243E-5, 
    2.113293E-5, 2.198657E-5, 2.287470E-5, 2.379870E-5, 2.476003E-5, 
    2.576018E-5, 2.680074E-5, 2.788333E-5, 2.900965E-5, 3.018147E-5, 
    3.140062E-5, 3.266902E-5, 3.398865E-5, 3.536159E-5, 3.678998E-5, 
    3.827608E-5, 3.982220E-5, 4.143078E-5, 4.310434E-5, 4.484550E-5, 
    4.665699E-5, 4.854165E-5, 5.050244E-5, 5.254244E-5, 5.466484E-5, 
    5.687297E-5, 5.917030E-5, 6.156043E-5, 6.404710E-5, 6.663422E-5, 
    6.932584E-5, 7.212619E-5, 7.503966E-5, 7.807081E-5, 8.122441E-5, 
    8.450539E-5, 8.791890E-5, 9.147030E-5, 9.516515E-5, 9.900925E-5, 
    1.030086E-4, 1.071695E-4, 1.114985E-4, 1.160024E-4, 1.206882E-4, 
    1.255633E-4, 1.306353E-4, 1.359122E-4, 1.414022E-4, 1.471140E-4, 
    1.530566E-4, 1.592391E-4, 1.656714E-4, 1.692285E-4, 1.720211E-4, 
    1.748599E-4, 1.777455E-4, 1.806787E-4, 1.836604E-4, 1.866912E-4, 
    1.897720E-4, 1.929037E-4, 1.960871E-4, 1.993230E-4, 2.026123E-4, 
    2.059559E-4, 2.093546E-4, 2.128095E-4, 2.163213E-4, 2.198911E-4, 
    2.235199E-4, 2.272085E-4, 2.309579E-4, 2.347693E-4, 2.386435E-4, 
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    int j = 0;
    for ( int i = 2500; i < 2760; ++i ){
      equal( sb[i], correct[j] );
      j += 1;
    }
    for ( int i = 0; i < 2501; ++i ){
      equal( sb[i], 0.0 );
    }

    for ( int i = 0; i < ap.size(); ++i ){
    ap[i] = (i+1)*0.0001;
    }

    for ( int i = 0; i < sb.size(); ++i ){
    sb[i] = 0.0; 
    }
    be = 0.015;
    betan = {0.015, 0.18, 0.22};
    correct = {0.0, 2.976482E-4, 2.922919E-4, 2.870320E-4, 2.818668E-4, 
    2.767946E-4, 2.718136E-4, 2.669223E-4, 2.621189E-4, 2.574020E-4, 
    2.527700E-4, 2.482214E-4, 2.437546E-4, 2.393682E-4, 2.350607E-4, 
    2.308307E-4, 2.266768E-4, 2.225977E-4, 2.185920E-4, 2.146584E-4, 
    2.107956E-4, 2.070023E-4, 2.032772E-4, 1.998421E-4, 1.983438E-4, 
    1.968567E-4, 1.953808E-4, 1.939160E-4, 1.924621E-4, 1.910191E-4, 
    1.895870E-4, 1.881656E-4, 1.867548E-4, 1.853547E-4, 1.839650E-4, 
    1.825857E-4, 1.812168E-4, 1.798582E-4, 1.785097E-4, 1.771714E-4, 
    1.758430E-4, 1.745247E-4, 1.732162E-4, 1.719175E-4, 1.706286E-4, 
    1.693493E-4, 1.680797E-4, 1.668195E-4, 1.655688E-4, 1.643275E-4, 
    1.630954E-4, 1.618726E-4, 1.606590E-4, 1.594545E-4, 1.582590E-4, 
    1.570725E-4, 1.558948E-4, 1.547260E-4, 1.535660E-4, 1.524147E-4, 
    1.512719E-4, 1.501378E-4, 1.490122E-4, 1.478950E-4, 1.467861E-4, 
    1.456856E-4, 1.445934E-4, 1.435093E-4, 1.424334E-4, 1.413655E-4, 
    1.403056E-4, 1.392537E-4, 1.382096E-4, 1.371734E-4, 1.361450E-4, 
    1.351243E-4, 1.341112E-4, 1.331057E-4, 1.321078E-4, 1.311173E-4, 
    1.301343E-4, 1.291586E-4, 1.281902E-4, 1.272291E-4, 1.262753E-4, 
    1.253285E-4, 1.243889E-4, 1.234563E-4, 1.225307E-4, 1.216120E-4, 
    1.207003E-4, 1.197953E-4, 1.188972E-4, 1.180058E-4, 1.171210E-4, 
    1.162429E-4, 1.153714E-4, 1.145064E-4, 1.136479E-4, 1.127959E-4, 
    1.119502E-4, 1.111109E-4, 1.102778E-4, 1.094510E-4, 1.086304E-4, 
    1.078160E-4, 1.070076E-4, 1.062054E-4, 1.054091E-4, 1.046188E-4, 
    1.038345E-4, 1.030560E-4, 1.022833E-4, 1.015165E-4, 1.007554E-4, 
    9.999999E-5, 9.925025E-5, 9.850614E-5, 9.776760E-5, 9.703460E-5, 
    9.630709E-5, 9.558504E-5, 9.486841E-5, 9.415714E-5, 9.423117E-5, 
    9.477307E-5, 9.531807E-5, 9.586622E-5, 9.641751E-5, 9.697197E-5, 
    9.752963E-5, 9.809049E-5, 9.865457E-5, 9.922190E-5, 9.979249E-5, 
    1.003663E-4, 1.009435E-4, 1.015240E-4, 1.021078E-4, 1.026950E-4, 
    1.032856E-4, 1.038795E-4, 1.044769E-4, 1.050777E-4, 1.056820E-4, 
    1.062897E-4, 1.069010E-4, 1.075157E-4, 1.081340E-4, 1.087558E-4, 
    1.093813E-4, 1.100103E-4, 1.106429E-4, 1.112792E-4, 1.119191E-4, 
    1.125627E-4, 1.132100E-4, 1.138611E-4, 1.145158E-4, 1.151744E-4, 
    1.158367E-4, 1.165028E-4, 1.171728E-4, 1.178466E-4, 1.185243E-4, 
    1.192059E-4, 1.198914E-4, 1.205809E-4, 1.212743E-4, 1.219717E-4, 
    1.226731E-4, 1.233786E-4, 1.240881E-4, 1.248017E-4, 1.255194E-4, 
    1.262412E-4, 1.269672E-4, 1.276973E-4, 1.284317E-4, 1.291702E-4, 
    1.299130E-4, 1.306601E-4, 1.314115E-4, 1.321672E-4, 1.329273E-4, 
    1.336917E-4, 1.344605E-4, 1.352337E-4, 1.360114E-4, 1.367936E-4, 
    1.375802E-4, 1.383714E-4, 1.391671E-4, 1.399674E-4, 1.407724E-4, 
    1.415819E-4, 1.423961E-4, 1.432149E-4, 1.440385E-4, 1.448668E-4, 
    1.456999E-4, 1.465378E-4, 1.473805E-4, 1.482280E-4, 1.490804E-4, 
    1.499377E-4, 1.508000E-4, 1.516672E-4, 1.525394E-4, 1.534166E-4, 
    1.542988E-4, 1.551861E-4, 1.560786E-4, 1.569761E-4, 1.578788E-4, 
    1.587867E-4, 1.596999E-4, 1.606183E-4, 1.615419E-4, 1.624709E-4, 
    1.634052E-4, 1.643449E-4, 1.652900E-4, 1.662405E-4, 1.674611E-4, 
    1.702246E-4, 1.730337E-4, 1.758892E-4, 1.787918E-4, 1.817423E-4, 
    1.847414E-4, 1.877901E-4, 1.908891E-4, 1.940392E-4, 1.972413E-4, 
    2.004963E-4, 2.038049E-4, 2.071682E-4, 2.105870E-4, 2.140621E-4, 
    2.175947E-4, 2.211855E-4, 2.248356E-4, 2.285459E-4, 2.323175E-4, 
    2.361512E-4, 2.400483E-4, 0.0, 0.0, 0.0};
    sbfill(sb, nbt, delta, be, ap, betan, ndmax );
    j = 0;
    for ( int i = 2429; i < 2679; ++i ){
      equal( sb[i], correct[j] );
      j += 1;
    }
    for ( int i = 0; i < 2429; ++i ){
      equal( sb[i], 0.0 );
    }
    for ( int i = 2679; i < ndmax; ++i ){
      equal( sb[i], 0.0 );
    }
              

    for ( int i = 0; i < ap.size(); ++i ){
    ap[i] = (i+1)*0.0001;
    }

    for ( int i = 0; i < sb.size(); ++i ){
    sb[i] = 0.0; 
    }
    be = 0.015;
    j = 0;
    betan = {0.015, 0.018, 0.022};
    correct = {2.5442136E-4, 2.1217272E-4, 1.5127199E-4, 9.9999997E-5, 
      6.6106083E-5, 4.3700144E-5, 2.8888454E-5, 1.9097026E-5, 1.2624296E-5, 
      8.3454283E-6, 5.5168360E-6, 3.6469643E-6, 4.0461258E-6, 6.1097007E-6, 
      9.2257245E-6, 1.3930959E-5, 2.1035923E-5, 3.1764507E-5, 4.7964804E-5, 
      7.2427455E-5, 1.0936636E-4, 1.6514458E-4, 2.1798446E-4, 2.6092250E-4};
    sbfill(sb, nbt, delta, be, ap, betan, ndmax );
    for ( int i = 2541; i < 2565; ++i ){
      equal( sb[i], correct[j] );
      j += 1;
    }
  } // GIVEN
  GIVEN( "invalid inputs" ){
    WHEN( "not even close to enough entries in sb, ap" ){
      int ndmax = 100;
      std::vector<double> sb (ndmax,0.0); 
      std::vector<double> ap (ndmax,0.0); 
      for ( int i = 0; i < ap.size(); ++i ){
        ap[i] = (i+1)*0.0001;
      }
      std::vector<double> betan {0.15, 0.18, 0.22};
      int nbt = 2545;
      double delta = 1.791435E-3, be = 0.15;
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( sbfill(sb, nbt, delta, be, ap, betan, ndmax ) );
      } // THEN
    } // WHEN

    WHEN( "just barely not enough entries (1 too few)" ){
      int ndmax = 5088;
      std::vector<double> sb (ndmax,0.0); 
      std::vector<double> ap (ndmax,0.0); 
      for ( int i = 0; i < ap.size(); ++i ){
        ap[i] = (i+1)*0.0001;
      }
      std::vector<double> betan {0.15, 0.18, 0.22};
      int nbt = 2545;
      double delta = 1.791435E-3, be = 0.15;
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( sbfill(sb, nbt, delta, be, ap, betan, ndmax ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // TEST CASE
