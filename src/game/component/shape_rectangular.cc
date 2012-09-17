// Header File
#include "game/component/shape_rectangular.h"

// External Dependencies
#include <list>
#include <set>

// Internal Dependencies
#include "game/action/movement.h"
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/graphic.h"
#include "utils/utils.h"

// Using
using std::list;
using std::set;
using game::action::Movement;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using utils::CompareDoubles;
using namespace utils::enums;

namespace game {
namespace component {

ShapeRectangular::ShapeRectangular(
        game::base::GameObject* owner, double size_x, double size_y,
        double stay_sizeclass, double pass_sizeclass, double enter_sizeclass
    )
  : super(owner, stay_sizeclass, pass_sizeclass, enter_sizeclass),
    dimensions_(ugdk::Vector2D(size_x,size_y)),
    bumps_() {
    bumps_.resize(4);
}
ShapeRectangular::~ShapeRectangular() {}

GameTile* ShapeRectangular::PlaceAt(GameTile* destination) {

    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Better safe than sorry.
    if(!TryPlace(destination)) { if(!occupying_tiles_.empty()) return occupying_tiles_.front(); else return nullptr; }

    // Remove yourself from the map.
    for( auto ot = occupying_tiles_.begin() ; ot != occupying_tiles_.end() ; ++ot )
        (*ot)->RemoveObject(this->owner_);
    occupying_tiles_.clear();

    // Add yourself to the new location.
    for( int j = 0 ; j < dimensions_.y ; ++j ) {
        for( int i = 0 ; i < dimensions_.x ; ++i ) {
            GameTile* tile = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j);
            occupying_tiles_.push_back(tile);
            tile->PushObject(owner_);
        }
    }

    // Update the nodes on the graphic component.
    this->owner_->graphic_component()->NodeLogic(occupying_tiles_);

    return destination;
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

    //TODO: Step logic. (sound, sensoryfield adjustments, etc...)

    const GameController* gamecontroller = GameController::reference();
    return PlaceAt(gamecontroller->GetTileByDirectionFromTile(occupying_tiles_.front(), TryStep(dir)));
}

bool ShapeRectangular::TryPlace(GameTile* destination) {

    if(!CheckForOob(destination)) return false;

    // Check for stuff where you're going.
    EvalBumpsAt(destination);

    if( !bumps_[0].empty() ) // there's something HUGE there (like a wall)
        return false; //TODO: implement wall-like bumps.
    else if( !bumps_[1].empty() || !bumps_[2].empty() || !bumps_[3].empty() ) //TODO: implement all these kinds of bumps.
        return false;

    // Otherwise there's nothing wrong with placing the hero there.
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

bool ShapeRectangular::CheckForOob(GameTile* destination) {
    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Check for out of bounds.
    if(destination == nullptr || gamecontroller->GetTileFromCoordinates(
                                     destination->x()+dimensions_.x-1,
                                     destination->y()+dimensions_.y-1
                                 ) == nullptr ) {
        return false;
    }
    return true;
}

void ShapeRectangular::EvalBumpsAt(GameTile* destination) {

    // !WARNING! //
    // Make sure to CheckForOob(-) before calling this!!!! //
    // !WARNING! //

    set<GameObject*> impassable_bumps, larger_bumps, equal_bumps, smaller_bumps;
    bumps_.clear();
    
    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    double their_pass = 0.0;
    double their_stay = 0.0;
    ord::Ord sizecomp = ord::EQ;

    // Let's find out what we're bumping into.
    for( int j = 0 ; j < dimensions_.y ; ++j ) {
        for( int i = 0 ; i < dimensions_.x ; ++i ) {
            const list<GameObject*> stuff = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j)->objects_here();
            for( auto ot = stuff.begin() ; ot != stuff.end() ; ++ot ) {
                if((*ot) != owner_) { // can't bump into self
                    their_pass = (*ot)->shape_component()->pass_sizeclass();
                    their_stay = (*ot)->shape_component()->stay_sizeclass();

                    if(their_stay == std::numeric_limits<double>::infinity()) // you have bumped into something impassable, like a wall.
                        impassable_bumps.insert(*ot);
                    else if( (CompareDoubles(their_pass, stay_sizeclass_) == ord::LT) &&  // you can't fit under that thing
                             (CompareDoubles(their_stay, pass_sizeclass_) == ord::GT) ) { // and that thing can't fit under you...

                        sizecomp = CompareDoubles(their_stay, stay_sizeclass_);
                        switch(sizecomp) {
                            case ord::GT: larger_bumps.insert(*ot); break;
                            case ord::EQ: equal_bumps.insert(*ot); break;
                            case ord::LT: smaller_bumps.insert(*ot); break;
                            default:
                                #ifdef DEBUG
                                fprintf(stderr,"CompareDoubles returned error value %i in ShapeRectangular::GetBumpsAt(-)\n", sizecomp);
                                #endif
                                break;
                        }
                    }
                }
            }
        }
    }

    bumps_.push_back(impassable_bumps);
    bumps_.push_back(larger_bumps);
    bumps_.push_back(equal_bumps);
    bumps_.push_back(smaller_bumps);
}

} // namespace component
} // namespace game