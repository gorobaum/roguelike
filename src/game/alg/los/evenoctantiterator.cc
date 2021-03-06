
// Header File
#include "game/alg/los/evenoctantiterator.h"

// External Dependencies
// (none)

// Internal Dependencies
#include <ugdk/math/integer2D.h>

// Using
using ugdk::math::Integer2D;

namespace game {
namespace alg {
namespace los {

EvenOctantIterator::EvenOctantIterator(double range_squared) : super(range_squared, Integer2D(0,0)) {}

EvenOctantIterator& EvenOctantIterator::operator++() {

    // don't move if we're at the end already.
    if( end() )
        return *this;

    // normal step case.
    if( focus_.x <= -(focus_.y) ) {
        ++(focus_.x);
        // gotta check for the range, and force an outer step in that case.
        if( end() ) {
            focus_.x = 0;
            --(focus_.y);
        }
    } else { // outer step case.
        focus_.x = 0;
        --(focus_.y);
    }

	return *this;
}

void EvenOctantIterator::Reset() {
    focus_ = Integer2D(0,0);
}

bool EvenOctantIterator::FocusIsControlTile() const {
	if(focus_.x - 1 == -(focus_.y) )
		return true;
	return false;
}

} // namespace los
} // namespace alg
} // namespace game
