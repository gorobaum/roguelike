#ifndef BADGAME_UTILS_H_
#define BADGAME_UTILS_H_

#include <cmath>
#include <limits>

namespace utils {

class Utils {
  public:
    static int CompareDoubles(double a, double b) {
        int expa = 0, expb = 0;
        std::frexp(a, &expa);
        std::frexp(b, &expb);

        if(expa > expb) return 1;
        else if(expa < expb) return -1;
        else {
            a -= b;
            if( a <= std::ldexp(std::numeric_limits<double>::epsilon(), expa) ) return 0;
            else { if(a>0) return 1; else return -1; }
        }
    }
};

} // namespace utils

#endif