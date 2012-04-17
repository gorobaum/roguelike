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
using std::list;
using game::action::Movement;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace component {

GameTile* ShapeRectangular::PlaceAt(GameTile* destination) {

    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Check for out of bounds.
    if(destination == nullptr || gamecontroller->GetTileFromCoordinates(
                                     destination->x()+static_cast<size_t>(dimensions_.x)-1,
                                     destination->y()+static_cast<size_t>(dimensions_.y)-1
                                 ) == nullptr ) {
        return occupying_tiles_.front(); //TODO: in case of diagonal movement, try to restrict to one coordinate.
    }

    // Check for impassable stuff where you're going.
    for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
        for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
            const list<GameObject*> stuff = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j)->objects_here();
            for( auto ot = stuff.begin() ; ot != stuff.end() ; ++ot ) {
                if( ((*ot) != this->owner_) /* can't bump into self */
                  && ( (*ot)->shape_component()->pass_sizeclass() <= stay_sizeclass_ ) /* this too big to pass under that */
                  && ( (*ot)->shape_component()->stay_sizeclass() >  pass_sizeclass_ ) /* that can't fit under this */ ) {
                    return occupying_tiles_.front();
                }
            }
        }
    }

    // Remove yourself from the map
    for( auto xt = occupying_tiles_.begin() ; xt != occupying_tiles_.end() ; ++xt )
        (*xt)->RemoveObject(this->owner_);
    occupying_tiles_.clear();

    // Add yourself to the new location
    for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
        for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
            GameTile* tile = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j);
            occupying_tiles_.push_back(tile);
            tile->PushObject(owner_);
        }
    }

    // Update the nodes on the graphic component.
    this->owner_->graphic_component()->NodeLogic(occupying_tiles_);

    return destination; //TODO: check for logic collisions.
}

GameTile* ShapeRectangular::Move(Movement& mov) {
    // Steps the movement one direction at a time, aborts on nullptr or returns the last Step(-).

    // for with lookahead.
    if( mov.dirs.size() == 0 ) return occupying_tiles_.front(); // make sure ++di exists.
    auto di = mov.dirs.begin();
    for( ; (++di) != mov.dirs.end() ; ++di ) {
        --di;
        if( Step(*di) == nullptr ) return nullptr;
    }
    --di;
    return Step(*di);
}

GameTile* ShapeRectangular::Step(Movement::Direction dir) {
    const GameController* gamecontroller = GameController::reference();

    GameTile* destination = gamecontroller->GetTileByDirectionFromTile(occupying_tiles_.front(), dir);
    return PlaceAt(destination);
}

} // namespace component
} // namespace game