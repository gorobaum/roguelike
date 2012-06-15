#ifndef BADGAME_UTILS_H_
#define BADGAME_UTILS_H_

#include <cmath>
#include <limits>

namespace utils {

class Utils {
  public:
    // Compares doubles taking into account their imprecision.
    // Returns 1 if a>b (FIRST larger than second), 2 if a<b (SECOND larger than first), and 0 if a==b.
    // Also returns -2 in case of errors, and -1 in case of double infinites (normally that means "incomparable").
    // Note: "CompareDoubles(a,b) == 0 && CompareDoubles(b,c) == 0 && CompareDoubles(a,c) != 0" might be true.
    static int CompareDoubles(double a, double b) {
        int neg = 0;            // negativeness of a and b
        int expa = 0, expb = 0; // exponent values of a and b
        static double eps = std::numeric_limits<double>::epsilon(); // double's epsilon.

        // checks for weird values...
        static double inf = std::numeric_limits<double>::infinity();
        static double qnan = std::numeric_limits<double>::quiet_NaN();
        static double snan = std::numeric_limits<double>::signaling_NaN();
        if( a == qnan || a == snan || b == qnan || b == snan ) return -2;
        if( a == inf ) if( b == inf ) return -1; else return 1;
        else if( b == inf ) return 2; 

        // extract negativeness
        if(a<0) { neg += 1; }
        if(b<0) { neg += 2; }

        // extract exponents and mantissae
        a = std::frexp(a, &expa);
        b = std::frexp(b, &expb);

        // wtf happened?
        if( a == 1.0 || b == 1.0 || (a == 0.0 && expa != 0) || (b == 0.0 && expb != 0) ) return -2;

        // different exponents case. expb will hold the old exponent value in the expa == expb case.
        // the number with the bigger exponent is the one whose sign decides the order.
        expa -= expb;
        if(expa < 0) switch(neg) { case 2: case 3: return 1;  case 0: case 1: return 2; } // b decides
        if(expa > 0) switch(neg) { case 0: case 2: return 1;  case 1: case 3: return 2; } // a decides

        a -= b; // mantissae difference, never falls out of bounds.
        if( a <= eps && a >= -eps ) return 0;
        if(a>0) return 1;
        return 2;
    }
};

} // namespace utils

#endif