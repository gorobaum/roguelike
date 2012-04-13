// Header File
#include "game/components/shape_rectangular.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/movement.h"
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"

// Using
using game::action::Movement;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace component {

GameTile* ShapeRectangular::PlaceAt(GameTile* destination) {
    
    for( auto xt = occupying_tiles_.begin() ; xt != occupying_tiles_.end() ; ++xt )
        (*xt)->RemoveObject(this->owner_);
    occupying_tiles_.clear();

    const GameController* gamecontroller = GameController::reference_;

    for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
        for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
            GameTile* tile = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j);
            occupying_tiles_.push_back(tile);
            tile->PushObject(owner_);
        }
    }

    return destination; //TODO: make use of this. (implement PlaceAt(...) deflecting or failing).
}

GameTile* ShapeRectangular::Move(Movement& mov) {
    const GameController* gamecontroller = GameController::reference_;
    return PlaceAt(gamecontroller->GetTileByMovementFromTile(occupying_tiles().front(), mov));
}

GameTile* ShapeRectangular::Step(Movement::Direction dir) {
    Movement mov;
    mov.dirs.push_back(dir);
    return Move(mov);
}

} // namespace component
} // namespace game