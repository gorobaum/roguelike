#ifndef ROGUELIKE_UTILS_H_
#define ROGUELIKE_UTILS_H_

namespace utils {

namespace enums {
namespace ord {
enum Ord {
    LT  = -1,
    EQ  =  0,
    GT  =  1,

    INC = -2,
    NAN = -3
};
}
}

// Compares doubles taking into account their imprecision.
// Returns ord::LT (-1) if a<b, ord::EQ (0) if a~==b, ord::GT (1) if a>b, ord::INC (-2) if a and b are infinites.
// Also returns ord::NAN (-3) if you try to compare a NaN.
// Note: "CompareDoubles(a,b) == ord::EQ && CompareDoubles(b,c) == ord::EQ && CompareDoubles(a,c) == ord::LT" might be true.
enums::ord::Ord CompareDoubles(double a, double b);

// Derp
enums::ord::Ord CompareInts(int a, int b);

} // namespace utils

#endif