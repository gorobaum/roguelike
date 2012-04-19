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
#include "utils/utils.h"

// Using
using std::list;
using game::action::Movement;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using utils::Utils;

namespace game {
namespace component {

GameTile* ShapeRectangular::PlaceAt(GameTile* destination) {

    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Better safe than sorry.
    if(!TryPlace(destination)) { if(!occupying_tiles_.empty()) return occupying_tiles_.front(); else return nullptr; }

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

    return destination; //TODO: run logic stuff.
}

GameTile* ShapeRectangular::Move(Movement& mov) {
    // Steps the movement one direction at a time, aborts on nullptr or returns the last Step(-).

    // you're nowhere? there's nothing I can do.
    if(occupying_tiles_.empty()) return nullptr;

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
    
    // you're nowhere? there's nothing I can do.
    if(occupying_tiles_.empty()) return nullptr;

    // no movement? no Place.
    if( TryStep(dir) == Movement::NONE ) return occupying_tiles_.front();

    const GameController* gamecontroller = GameController::reference();
    return PlaceAt(gamecontroller->GetTileByDirectionFromTile(occupying_tiles_.front(), TryStep(dir)));
}

bool ShapeRectangular::TryPlace(GameTile* destination) {

    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Check for out of bounds.
    if(destination == nullptr || gamecontroller->GetTileFromCoordinates(
                                     destination->x()+static_cast<size_t>(dimensions_.x)-1,
                                     destination->y()+static_cast<size_t>(dimensions_.y)-1
                                 ) == nullptr ) {
        return false;
    }

    // Check for impassable stuff where you're going.
    for( size_t j = 0 ; j < dimensions_.y ; ++j ) {
        for( size_t i = 0 ; i < dimensions_.x ; ++i ) {
            const list<GameObject*> stuff = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j)->objects_here();
            for( auto ot = stuff.begin() ; ot != stuff.end() ; ++ot ) {
                if( ((*ot) != this->owner_) // can't bump into self
                  && ( Utils::CompareDoubles( (*ot)->shape_component()->pass_sizeclass(), stay_sizeclass_ ) == -1 )     // this can't fit under that */
                  && ( Utils::CompareDoubles( (*ot)->shape_component()->stay_sizeclass(), pass_sizeclass_ ) ==  1 ) ) { // that can't fit under this */
                    return false;
                }
            }
        }
    }

    return true;
}

Movement::Direction ShapeRectangular::TryStep(Movement::Direction dir) {

    // you're nowhere? there's nothing I can do.
    if(occupying_tiles_.empty()) return Movement::NONE;

    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    GameTile* destination = gamecontroller->GetTileByDirectionFromTile(occupying_tiles_.front(), dir);

    // Trying to stand still doesn't move you.
    // Moving diagonally requires at least one of the corners free.
    // Trying to move diagonally will try to deflect your movement to one coord should it fail.
    switch(dir) {
        case Movement::NONE: return Movement::NONE;
        case Movement::UP_LEFT:
            if( ( TryStep(Movement::UP) || TryStep(Movement::LEFT) ) && TryPlace(destination) ) return Movement::UP_LEFT;
            else if(TryStep(Movement::UP)    && !TryStep(Movement::LEFT)) return Movement::UP;
            else if(TryStep(Movement::LEFT)  && !TryStep(Movement::UP)  ) return Movement::LEFT;
            else return Movement::NONE;
        case Movement::UP_RIGHT:
            if( (TryStep(Movement::UP) || TryStep(Movement::RIGHT)) && TryPlace(destination) ) return Movement::UP_RIGHT;
            else if(TryStep(Movement::UP)    && !TryStep(Movement::RIGHT)) return Movement::UP;
            else if(TryStep(Movement::RIGHT) && !TryStep(Movement::UP)   ) return Movement::RIGHT;
            else return Movement::NONE;
        case Movement::DOWN_LEFT:
            if( (TryStep(Movement::DOWN) || TryStep(Movement::LEFT)) && TryPlace(destination) ) return Movement::DOWN_LEFT;
            else if(TryStep(Movement::DOWN) && !TryStep(Movement::LEFT)) return Movement::DOWN;
            else if(TryStep(Movement::LEFT) && !TryStep(Movement::DOWN)) return Movement::LEFT;
            else return Movement::NONE;
        case Movement::DOWN_RIGHT:
            if( (TryStep(Movement::DOWN) || TryStep(Movement::RIGHT)) && TryPlace(destination) ) return Movement::DOWN_RIGHT;
            else if(TryStep(Movement::DOWN)  && !TryStep(Movement::RIGHT)) return Movement::DOWN;
            else if(TryStep(Movement::RIGHT) && !TryStep(Movement::DOWN) ) return Movement::RIGHT;
            else return Movement::NONE;
        default: if(TryPlace(destination)) return dir; else return Movement::NONE;
    }
}

} // namespace component
} // namespace game