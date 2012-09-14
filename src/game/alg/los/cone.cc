
// Header File
#include "game/alg/los/cone.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "utils/utils.h"

// Using
using ugdk::math::Integer2D;
using namespace game::alg::los::enums;
using namespace utils::enums;

namespace game {
namespace alg {
namespace los {

Cone::Cone(const EquationalLine& upper, const EquationalLine& lower)
  : upper_(upper), lower_(lower) {}

bump::BumpType Cone::ComputeBumpType(const ugdk::math::Integer2D& up_left) {

    Integer2D upper_corner = up_left;
    Integer2D lower_corner = upper_corner + Integer2D(1,1);

    // cases above bump, and below bump.

    ord::Ord cmp = upper_.CompareWithInteger2D(lower_corner);
    if( cmp == ord::GT || cmp == ord::EQ )
        return bump::ABV;

    cmp = lower_.CompareWithInteger2D(upper_corner);
    if( cmp == ord::LT || cmp == ord::EQ )
        return bump::BLW;

    // in all cases below, the cone intersects the target.

    cmp = upper_.CompareWithInteger2D(upper_corner);
    if( cmp == ord::GT ) {
        // in this case, upper_ intersects the tile strictly.
        // we need to decide whether it's a block or an upper bump.
        cmp = lower_.CompareWithInteger2D(lower_corner);
        if( cmp == ord::LT )
            return bump::BLK;

        return bump::UPR;
    }

    // in all cases below, upper_ is above the upper_corner.

    cmp = lower_.CompareWithInteger2D(lower_corner);
    if( cmp == ord::LT )
        return bump::LWR;

    return bump::MDL;
}

void Cone::UpperBump(const ugdk::math::Integer2D& up_left) {
    Integer2D limit = up_left + Integer2D(1,1);

    // fix the problem at hand:
    upper_.set_target(limit);
    
    // check if we didn't introduce any errors:
    for(auto st = lower_bumps_.end(); st != lower_bumps_.begin();) {
        --st;
        if( upper_.CompareWithInteger2D(*st) == ord::GT ) {
            upper_.set_origin(*st);
            break;
        }
    }
    
    // update the upper bumps list.
    upper_bumps_.push_back(limit);
}

void Cone::LowerBump(const ugdk::math::Integer2D& up_left) {
    Integer2D limit = up_left;

    lower_.set_target(limit);
    
    for(auto st = upper_bumps_.end(); st != upper_bumps_.begin();) {
        --st;
        if( lower_.CompareWithInteger2D(*st) == ord::LT ) {
            lower_.set_origin(*st);
            //TODO: remove old bumps from the list?
            break;
        }
    }
    
    lower_bumps_.push_back(limit);
}

} // namespace los
} // namespace alg
} // namespace game
