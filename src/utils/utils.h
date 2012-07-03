#ifndef BADGAME_UTILS_H_
#define BADGAME_UTILS_H_

#include <cmath>
#include <limits>

namespace utils {

enum Ord {
    LT  = -1,
    EQ  =  0,
    GT  =  1,

    INC = -2,
    NAN = -3,
    ERR = -4
};


// Compares doubles taking into account their imprecision.
// Returns utils::LT (-1) if a<b, utils::EQ (0) if a==b, utils::GT (1) if a<b, utils::INC (-2) if a and b are infinites.
// Also returns utils::NAN (-3) if you try to compare a NaN, and utils::ERR (-4) if some error occurs.
// Note: "CompareDoubles(a,b) == utils::EQ && CompareDoubles(b,c) == utils::EQ && CompareDoubles(a,c) == utils::LT" might be true.
static Ord CompareDoubles(double a, double b) {
    int neg = 0;            // negativeness of a and b
    int expa = 0, expb = 0; // exponent values of a and b
    static double eps = std::numeric_limits<double>::epsilon();
    static double inf = std::numeric_limits<double>::infinity();
    static double qnan = std::numeric_limits<double>::quiet_NaN();
    static double snan = std::numeric_limits<double>::signaling_NaN();

    // check for NaNs
    if( a == qnan || a == snan || b == qnan || b == snan ) return NAN;

    // check for infinites
    if( a == inf ) {
        if( b == inf ) return INC;
        else return GT;
    } else if( b == inf ) return LT; 

    // extract negativeness
    if(a<0) { neg += 1; }
    if(b<0) { neg += 2; }

    // extract exponents and significands
    a = std::frexp(a, &expa);
    b = std::frexp(b, &expb);

    // wtf happened?
    if( a == 1.0 || b == 1.0 || (a == 0.0 && expa != 0) || (b == 0.0 && expb != 0) ) return ERR;

    // we need to compare expoents now.
    expa -= expb;
    
    // different exponents case. expb will hold the old exponent value in the expa == expb case.
    // the number with the bigger exponent is the one whose sign decides the order,
    // except in the case where the difference is 1. In this case more calculations are necessary.
    if(expa < 0) {
        if(expa == -1) { b -= ldexp(a,-1); if( b <= eps && b >= -eps ) return EQ; }
        switch(neg) { case 2: case 3: return GT; case 0: case 1: return LT; } // b decides
    }
    if(expa > 0) {
        if(expa ==  1) { a -= ldexp(b,-1); if( a <= eps && a >= -eps ) return EQ; }
        switch(neg) { case 0: case 2: return GT; case 1: case 3: return LT; } // a decides
    }

    // equal expoents case. Significands define the order.
    a -= b;
    if( a <= eps && a >= -eps ) return EQ;
    if(a>0) return GT;
    return LT;
}

} // namespace utils

#endif