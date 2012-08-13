
// Header File
#include "game/alg/losoctant.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/alg/evenoctantiterator.h"
#include "game/alg/oddoctantiterator.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameController;
using game::base::GameTile;

namespace game {
namespace alg {

LoSOctant::LoSOctant(int id, double range_squared) : rotations_(id/2) {
    if( id%2 == 0 )
        iterator_ = new EvenOctantIterator(range_squared);
    else
        iterator_ = new OddOctantIterator(range_squared);
}

LoSOctant::~LoSOctant() { delete iterator_; }

bool LoSOctant::OutOfBounds(const ugdk::math::Integer2D& coords) const {
    const GameController* gamecontroller = GameController::reference();

    return gamecontroller->TileOutOfBounds(coords);
}


std::list<base::GameObject*>& LoSOctant::ObjectsAtFocus() const {
    const GameController* gamecontroller = GameController::reference();

    Integer2D coords = **iterator_;
    for(int i=0; i<rotations_; ++i)
        coords.Rotate(ugdk::math::NINETY);
    GameTile* tile = gamecontroller->GetTileFromCoordinates(coords);

    return tile->objects_here();
}

} // namespace alg
} // namespace game
