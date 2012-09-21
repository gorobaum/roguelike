
// Header File
#include "game/alg/los/octant.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/alg/los/evenoctantiterator.h"
#include "game/alg/los/oddoctantiterator.h"
#include "game/base/gamecontroller.h" // needed for FocusIsOutOfBounds(). //TODO: remove.

// Using
using ugdk::math::Integer2D;
using game::base::GameController;

namespace game {
namespace alg {
namespace los {

Octant::Octant(int id, double range_squared)
  : parity_(id%2), rotations_(id/2), origin_(42,42) {

    if( parity_ == 0 )
        iterator_ = new EvenOctantIterator(range_squared);
    else
        iterator_ = new OddOctantIterator(range_squared);
}

Octant::~Octant() { delete iterator_; }

Integer2D Octant::FocusCoordinates() const {
    Integer2D offset = **iterator_;
    for(int i=0; i<rotations_; ++i)
        offset.Rotate(ugdk::math::NINETY);

    offset += origin_;
    return offset;
}

bool Octant::FocusIsOutOfBounds() const {
    const GameController* gamecontroller = GameController::reference();

    return gamecontroller->TileOutOfBounds(FocusCoordinates());
}

bool Octant::FocusIsControlTile() const {
	return iterator_->FocusIsControlTile();
}

} // namespace los
} // namespace alg
} // namespace game
