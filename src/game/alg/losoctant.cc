
// Header File
#include "game/alg/losoctant.h"

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/losprocessor.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"
#include "game/components/vision.h"

// Using
using ugdk::Vector2D;
using game::base::GameTile;

namespace game {
namespace alg {

LoSOctant::iterator::iterator(const LoSOctant* owner, double range_squared)
  : owner_(owner), count_outer_(0), count_inner_(0), range_squared_(range_squared) {

    const base::GameController* gamecontroller = base::GameController::reference();

    int start_iter_x = 0, start_iter_y = 0;

    switch(owner->orientation()) {
        case 1:  start_iter_x =  1; start_iter_y = -2; break;
        case 2:  start_iter_x =  2; start_iter_y = -1; break;
        case 4:  start_iter_x =  2; start_iter_y =  1; break;
        case 5:  start_iter_x =  1; start_iter_y =  2; break;
        case 7:  start_iter_x = -1; start_iter_y =  2; break;
        case 8:  start_iter_x = -2; start_iter_y =  1; break;
        case 10: start_iter_x = -2; start_iter_y = -1; break;
        case 11: start_iter_x = -1; start_iter_y = -2; break;
        default: break;
    }

    GameTile* eye = owner->owner()->vision()->eye();

    focus_ = (outer_focus_ = gamecontroller->GetTileFromCoordinates(eye->x()+start_iter_x,eye->y()+start_iter_y));
}

LoSOctant::iterator::~iterator() {}

LoSOctant::iterator& LoSOctant::iterator::operator++() {

    switch(owner_->orientation()) {
        case 1:  step( 1, 0, 0,-1); break;
        case 2:  step( 0,-1, 1, 0); break;
        case 4:  step( 0, 1, 1, 0); break;
        case 5:  step( 1, 0, 0, 1); break;
        case 7:  step(-1, 0, 0, 1); break;
        case 8:  step( 0, 1,-1, 0); break;
        case 10: step( 0,-1,-1, 0); break;
        case 11: step(-1, 0, 0,-1); break;
        default: break;
    }

    return (*this);
}

void LoSOctant::iterator::step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    if(count_outer_ <= count_inner_) {
        step_jump(delta_x_out, delta_y_out);
    } else {
        focus_ = gamecontroller->GetTileFromCoordinates(focus_->x()+delta_x_in,focus_->y()+delta_y_in);

        if(focus_ == nullptr
           || Vector2D(focus_->x() - owner_->owner()->vision()->eye()->x() ,
                       focus_->y() - owner_->owner()->vision()->eye()->y()).LengthSquared() > range_squared_) {

            step_jump(delta_x_out, delta_y_out);
        }
        ++count_inner_;
    }
}

void LoSOctant::iterator::step_jump(int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    focus_ = (outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,
                                                                    outer_focus_->y()+delta_y_out) );
    ++count_outer_;
    count_inner_ = 0;
}


} // namespace alg
} // namespace game
