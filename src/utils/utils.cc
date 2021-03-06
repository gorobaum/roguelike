
#include <cmath>
#include <limits>
#include "utils/utils.h"

using namespace utils::enums;

namespace utils {

#undef D_EPS
#undef D_INF

static double D_EPS = std::numeric_limits<double>::epsilon() * 8;
static double D_INF = std::numeric_limits<double>::infinity();

ord::Ord CompareDoubles(double a, double b) {
    int neg = 0;            // negativeness of a and b
    int expa = 0, expb = 0; // exponent values of a and b

    // check for NaNs
    if( a != a || b != b ) return ord::ERR;

    // check for infinites
    if( a == D_INF ) {
        if( b == D_INF ) return ord::INC;
        else return ord::GT;
    } else if( b == D_INF ) return ord::LT; 

	// if a or b are 0.0, frexp behaves differently, and our treatment with exponentials wouldn't work.
	if(a == 0.0) {
		if( b <= D_EPS && b >= -D_EPS ) return ord::EQ;
		if( b>0 ) return ord::LT;
		return ord::GT;
	} else if(b == 0.0) {
		if( a <= D_EPS && a >= -D_EPS ) return ord::EQ;
		if(a>0) return ord::GT;
		return ord::LT;
	}

    // extract negativeness
    if(a<0) { neg += 1; }
    if(b<0) { neg += 2; }

    // extract exponents and significands
    a = std::frexp(a, &expa);
    b = std::frexp(b, &expb);

    // we need to compare expoents now.
    expa -= expb;
    
    // different exponents case. expb will hold the old exponent value in the expa == expb case.
    // the number with the bigger exponent is the one whose sign decides the order,
    // except in the case where the difference is 1. In this case more calculations are necessary.
    if(expa < 0) {
        if(expa == -1) { b -= ldexp(a,-1); if( b <= D_EPS && b >= -D_EPS ) return ord::EQ; }
        switch(neg) { case 2: case 3: return ord::GT; case 0: case 1: return ord::LT; } // b decides
    }
    if(expa > 0) {
        if(expa ==  1) { a -= ldexp(b,-1); if( a <= D_EPS && a >= -D_EPS ) return ord::EQ; }
        switch(neg) { case 0: case 2: return ord::GT; case 1: case 3: return ord::LT; } // a decides
    }

    // equal expoents case. Significands define the order.
    a -= b;
    if( a <= D_EPS && a >= -D_EPS ) return ord::EQ;
    if(a>0) return ord::GT;
    return ord::LT;
}

ord::Ord CompareInts(int a, int b) {
    a -= b;
    if(a > 0) return ord::GT;
    if(a < 0) return ord::LT;
    return ord::EQ;
}

} // utils