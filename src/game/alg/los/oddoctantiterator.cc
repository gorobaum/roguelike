
// Header File
#include "game/alg/los/oddoctantiterator.h"

// External Dependencies
// (none)

// Internal Dependencies
#include <ugdk/math/integer2D.h>

// Using
using ugdk::math::Integer2D;

namespace game {
namespace alg {
namespace los {

OddOctantIterator::OddOctantIterator(double range_squared) : super(range_squared, Integer2D(2,-1)) {}

OddOctantIterator& OddOctantIterator::operator++() {

    // don't move if we're at the end already.
    if( end() )
        return *this;

    // normal step case.
    if( -(focus_.y) + 1 < focus_.x ) {
        --(focus_.y);
        // gotta check for the range, and force an outer step in that case.
        if( end() ) {
            focus_.y = -1;
            ++(focus_.x);
        }
    }

    // outer step case.
    if( -(focus_.y) + 1 >= focus_.x ) {
        focus_.y = -1;
        ++(focus_.x);
    }
}

void OddOctantIterator::reset() {
    focus_ = Integer2D(2,-1);
}

} // namespace los
} // namespace alg
} // namespace game
