
// Header File
#include "game/alg/evenoctantiterator.h"

// External Dependencies
// (none)

// Internal Dependencies
#include <ugdk/math/integer2D.h>

// Using
using ugdk::math::Integer2D;

namespace game {
namespace alg {

EvenOctantIterator::EvenOctantIterator(double range_squared) : super(range_squared, Integer2D(1,-2)) {}

EvenOctantIterator& EvenOctantIterator::operator++() {

    // don't move if we're at the end already.
    if( end() )
        return *this;

    // normal step case.
    if( focus_.x + 1 < -(focus_.y) ) {
        ++(focus_.x);
        // gotta check for the range, and force an outer step in that case.
        if( end() ) {
            focus_.x = 1;
            --(focus_.y);
        }
    }

    // outer step case.
    if( focus_.x + 1 >= -(focus_.y) ) {
        focus_.x = 1;
        --(focus_.y);
    }
}

} // namespace alg
} // namespace game
