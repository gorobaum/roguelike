
// Header File
#include "game/alg/los/cone.h"

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "utils/utils.h"

// Using
using ugdk::Vector2D;
using namespace game::alg::los::enums;
using namespace utils::enums;

namespace game {
namespace alg {
namespace los {

Cone::Cone(const EquationalLineDouble& upper, const EquationalLineDouble& lower)
  : upper_(upper), lower_(lower) {}

bump::BumpType Cone::ComputeBumpType(const Vector2D& up_left) {

    Vector2D upper_corner = up_left;
    Vector2D lower_corner = upper_corner + Vector2D(1,1);

    // cases above bump, and below bump.

    ord::Ord cmp = upper_.CompareWith(lower_corner);
    if( cmp == ord::GT || cmp == ord::EQ )
        return bump::ABV;

    cmp = lower_.CompareWith(upper_corner);
    if( cmp == ord::LT || cmp == ord::EQ )
        return bump::BLW;

    // in all cases below, the cone intersects the target.

    cmp = upper_.CompareWith(upper_corner);
    if( cmp == ord::GT ) {
        // in this case, upper_ intersects the tile strictly.
        // we need to decide whether it's a block or an upper bump.
        cmp = lower_.CompareWith(lower_corner);
        if( cmp == ord::LT )
            return bump::BLK;

        return bump::UPR;
    }

    // in all cases below, upper_ is above the upper_corner.

    cmp = lower_.CompareWith(lower_corner);
    if( cmp == ord::LT )
        return bump::LWR;

    return bump::MDL;
}

void Cone::UpperBump(const Vector2D& up_left) {
    Vector2D limit = up_left + Vector2D(1,1);

    // fix the issue at hand:
    upper_.set_target(limit);
    
    // check if we didn't introduce any errors:
    for(auto st = lower_bumps_.rbegin() ; st != lower_bumps_.rend() ; ++st ) {
        if( upper_.CompareWith(*st) == ord::GT ) {
            upper_.set_origin(*st);
            break;
        }
    }
    
    // update the upper bumps list.
    upper_bumps_.push_back(limit);
}

void Cone::LowerBump(const Vector2D& up_left) {
    Vector2D limit = up_left;

    lower_.set_target(limit);
    
    for(auto st = upper_bumps_.rbegin() ; st != upper_bumps_.rend() ; ++st ) {
        if( lower_.CompareWith(*st) == ord::LT ) {
            lower_.set_origin(*st);
            break;
        }
    }
    
    lower_bumps_.push_back(limit);
}

} // namespace los
} // namespace alg
} // namespace game
