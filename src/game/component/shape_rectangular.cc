// Header File
#include "game/component/shape_rectangular.h"

// External Dependencies
#include <list>
#include <set>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/graphic.h"
#include "utils/utils.h"

// Using
using std::list;
using std::set;
using ugdk::math::Integer2D;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using utils::CompareDoubles;
using namespace utils::enums;

namespace game {
namespace component {

ShapeRectangular::ShapeRectangular(
        game::base::GameObject* owner, int size_x, int size_y,
        double stay_sizeclass, double pass_sizeclass, double enter_sizeclass
    )
  : super(owner, stay_sizeclass, pass_sizeclass, enter_sizeclass),
    dimensions_(Integer2D(size_x,size_y)),
    bumps_() {
    bumps_.resize(4);
}
ShapeRectangular::~ShapeRectangular() {}

const Integer2D& ShapeRectangular::PlaceAt(const Integer2D& destination) {

    // we'll need to access the tiles (to remove and add ourselves to the tiles).
    const GameController* gamecontroller = GameController::reference();

    if(!TryPlace(destination)) {
        assert(!occupying_tiles_.empty());
        return occupying_tiles_.front();
    }

    // Remove yourself from the map.
    for( auto ot = occupying_tiles_.begin() ; ot != occupying_tiles_.end() ; ++ot )
		gamecontroller->Tile(*ot)->RemoveObject(this->owner_);
    occupying_tiles_.clear();

    // Add yourself to the new location.
    for( int j = 0 ; j < dimensions_.y ; ++j ) {
        for( int i = 0 ; i < dimensions_.x ; ++i ) {
			Integer2D dest_tile(destination.x+i, destination.y+j);

            GameTile* tile = gamecontroller->Tile(dest_tile);
            occupying_tiles_.push_back(dest_tile);
            tile->PushObject(owner_);
        }
    }

    // Update the nodes on the graphic component.
    owner_->graphic_component()->NodeLogic(occupying_tiles_);

    return destination;
}

const Integer2D& ShapeRectangular::Move(const list<Integer2D>& mov) {
    // Steps the movement one direction at a time, aborts on nullptr or returns the last Step().

    assert(!occupying_tiles_.empty());

    // for with lookahead.
    if( mov.size() == 0 ) return occupying_tiles_.front(); // make sure ++di exists.
    auto di = mov.begin();
    for( ; (++di) != mov.end() ; ++di ) {
        --di;
        //TODO: use a better ugdk.
        Integer2D cmp = occupying_tiles_.front() - Step(*di);
        if( cmp.x == 0 && cmp.y == 0 ) return Step(*di);
    }
    --di;
    return Step(*di);
}

const Integer2D& ShapeRectangular::Step(const Integer2D& dir) {
    
    assert(!occupying_tiles_.empty());

    // no movement? no Place.
    //TODO: use a better ugdk
    Integer2D cmp = TryStep(dir); // - Integer2D(0,0);
    if( cmp.x == 0 && cmp.y == 0 ) return occupying_tiles_.front();

    //TODO: Step logic. (sound, sensoryfield adjustments, etc...)

    Integer2D destination = occupying_tiles_.front() + TryStep(dir);
    return PlaceAt(destination);
}

bool ShapeRectangular::TryPlace(const Integer2D& destination) {

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

Integer2D ShapeRectangular::TryStep(const Integer2D& dir) {

    assert(!occupying_tiles_.empty());
    
    // Moving diagonally requires at least one of the corners free.
    // Trying to move diagonally will try to deflect your movement to one coord should it fail,
    //   but will never decide between two valid alternatives.
    Integer2D destination = occupying_tiles_.front() + dir;

    if(dir.x == 0 || dir.y == 0) return TryPlace(destination) ? dir : Integer2D(0,0);

    Integer2D dir_x = Integer2D(dir.x, 0);
    Integer2D dir_y = Integer2D(0, dir.y);

    if( (TryStep(dir_x).x != 0 || TryStep(dir_y).y != 0) && TryPlace(destination) ) return dir;
    else if( TryStep(dir_x).x != 0 && TryStep(dir_y).y == 0 ) return TryStep(dir_x);
    else if( TryStep(dir_x).x == 0 && TryStep(dir_y).y != 0 ) return TryStep(dir_y);
    return Integer2D(0,0);
}

bool ShapeRectangular::CheckForOob(const ugdk::math::Integer2D& destination) {
    // we'll need to access the tiles.
    const GameController* gamecontroller = GameController::reference();

    // Check for out of bounds.
    if( gamecontroller->TileOutOfBounds(destination)
		|| gamecontroller->TileOutOfBounds(destination + dimensions_ - Integer2D(1,1)) ) {
        return false;
    }
    return true;
}

void ShapeRectangular::EvalBumpsAt(const ugdk::math::Integer2D& destination) {

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
            const set<GameObject*> stuff = gamecontroller->Tile(destination + Integer2D(i,j))->objects_here();
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