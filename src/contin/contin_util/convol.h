#include <iostream>
#include <stdlib.h> // abs()


template <typename F, typename A>
auto getTnVal( int j, const A& tn, const F& delta ){
  if (abs(j) >= int(tn.size())){ return 0.0; }
  if (j < 0){ return tn[abs(j)]*exp(j*delta); }
  return tn[abs(j)];
}


template <typename A, typename Range, typename B>
auto getConvolAtPoint( int i, const A& t1, const B& t2, const Range betaGrid ){
  int len_t1 = int(t1.size());
  double sumVal = 0.0, val_L, val_R;
  for (int j = -len_t1+1; j < len_t1-1; ++j){
    if (i-j  >= int(t2.size())){ return sumVal; }
    auto delta = abs(betaGrid[abs(j+1)] - betaGrid[abs(j)]);
    val_L = getTnVal(j,  t1,delta)*getTnVal(i-j,    t2,delta);
    val_R = getTnVal(j+1,t1,delta)*getTnVal(i-(j+1),t2,delta);
    sumVal += (val_L + val_R)*0.5*delta;
  }
  return sumVal;
}


template <typename Range, typename Array>
auto convol( const Range& t1, const Array& t2, int len_t3, const Array betaGrid){
  Array t3(t2.size(),0.0);
 
  for (int i = 0; i<len_t3; ++i){
    t3[i] = getConvolAtPoint(i,t1,t2,betaGrid);
  }
  return t3;
}




/*
template <typename F, typename A>
auto getConvolAtPoint( int i, F delta, const A& t1, const A& t2){
  int len_t1 = int(t1.size());
  F sumVal = 0.0;
  for ( int j = -len_t1+1; j < len_t1; ++j ){
    if ( i - j  >= int(t2.size()) ){ return sumVal; }
    F value = getTnVal( j, t1, delta ) * getTnVal( i-j, t2, delta );
    sumVal += (abs(j) == len_t1-1) ? value * 0.5 * delta : value * delta;
  }
  return sumVal;
}
*/


