
// Header File
#include "game/alg/losprocessor.h"

// External Dependencies

// Internal Dependencies
#include "game/base/gamecontroller.h"   // iterator& operator++()
#include "game/base/gametile.h"         // focus_, outer_focus_
#include "game/components/vision.h"     // eye()

// Using

namespace game {
namespace alg {
LosOctant::iterator::iterator(const LosOctant* owner)
  : owner_(owner), count_outer_(0), count_inner_(0),
    focus_(owner->owner()->vision()->eye()),
    outer_focus_(owner->owner()->vision()->eye()) {}

LosOctant::iterator::~iterator() {}

LosOctant::iterator& LosOctant::iterator::operator++() {

    switch(owner_->orientation()) {
        case 1:  step( 1, 0, 0, 1); break;
        case 2:  step( 0, 1, 1, 0); break;
        case 4:  step( 0,-1, 1, 0); break;
        case 5:  step( 1, 0, 0,-1); break;
        case 7:  step(-1, 0, 0,-1); break;
        case 8:  step( 0,-1,-1, 0); break;
        case 10: step( 0, 1,-1, 0); break;
        case 11: step(-1, 0, 0, 1); break;
        default: step( 0, 0, 0, 0); break;
    }

    return (*this);
}

void LosOctant::iterator::step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    if(count_outer_ <= count_inner_) {
        focus_ = outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,outer_focus_->y()+delta_y_out);
        ++count_outer_;
        count_inner_ = 0;
    } else {
        focus_ = gamecontroller->GetTileFromCoordinates(focus_->x()+delta_x_in,focus_->y()+delta_y_in);
        ++count_inner_;
    }
}


} // namespace alg
} // namespace game