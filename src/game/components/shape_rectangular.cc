// Header File
#include "game/components/shape_rectangular.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/movement.h"
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/graphic.h"

// Using
using game::action::Movement;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace component {

GameTile* ShapeRectangular::PlaceAt(GameTile* destination) {

    const GameController* gamecontroller = GameController::reference();

    if(destination == nullptr || gamecontroller->GetTileFromCoordinates(
                                     destination->x()+static_cast<size_t>(dimensions_.x)-1,
                                     destination->y()+static_cast<size_t>(dimensions_.y)-1
                                 ) == nullptr ) {
        return occupying_tiles_.front();
    }

    for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
        for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
            if( gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j) == nullptr )
                return occupying_tiles_.front();
        }
    }


    for( auto xt = occupying_tiles_.begin() ; xt != occupying_tiles_.end() ; ++xt )
        (*xt)->RemoveObject(this->owner_);
    occupying_tiles_.clear();



    for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
        for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
            GameTile* tile = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j);
            occupying_tiles_.push_back(tile);
            tile->PushObject(owner_);
        }
    }

    this->owner_->graphic_component()->NodeLogic(occupying_tiles_);

    return destination; //TODO: check for collisions, 
}

GameTile* ShapeRectangular::Move(Movement& mov) {
    const GameController* gamecontroller = GameController::reference();
    return PlaceAt(gamecontroller->GetTileByMovementFromTile(occupying_tiles().front(), mov));
}

GameTile* ShapeRectangular::Step(Movement::Direction dir) {
    Movement mov;
    mov.dirs.push_back(dir);
    return Move(mov);
}

} // namespace component
} // namespace game