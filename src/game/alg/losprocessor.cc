
// Header File
#include "game/alg/losprocessor.h"

// External Dependencies
#include <set>

// Internal Dependencies
#include "game/base/gamecontroller.h"   // iterator& operator++()
#include "game/base/gametile.h"         // focus_, outer_focus_
#include "game/components/vision.h"     // eye()

// Using

namespace game {
namespace alg {
LosOctant::iterator::iterator(const LosOctant* owner)
  : owner_(owner), count_outer_(0), count_inner_(0),
    focus_(owner->owner()->vision()->eye()) {

    const base::GameController* gamecontroller = base::GameController::reference();

    int start_iter_x = 0, start_iter_y = 0;

    switch(owner->orientation()) {
        case 1:  start_iter_x =  1; start_iter_y =  2; break;
        case 2:  start_iter_x =  2; start_iter_y =  1; break;
        case 4:  start_iter_x =  2; start_iter_y = -1; break;
        case 5:  start_iter_x =  1; start_iter_y = -2; break;
        case 7:  start_iter_x = -1; start_iter_y = -2; break;
        case 8:  start_iter_x = -2; start_iter_y = -1; break;
        case 10: start_iter_x = -2; start_iter_y =  1; break;
        case 11: start_iter_x = -1; start_iter_y =  2; break;
        default: break;
    }

    base::GameTile* eye = owner->owner()->vision()->eye();

    outer_focus_ = gamecontroller->GetTileFromCoordinates(eye->x()+start_iter_x,eye->y()+start_iter_y);
}

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
        default: break;
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

LosOctant::iterator& LosOctant::iterator::jump() {
    switch(owner_->orientation()) {
        case 1: case 11: step_jump( 0, 1); break;
        case 2: case  4: step_jump( 1, 0); break;
        case 5: case  7: step_jump( 0,-1); break;
        case 8: case 10: step_jump(-1, 0); break;
        default: break;
    }

    return (*this);
}

void LosOctant::iterator::step_jump(int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    focus_ = outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,outer_focus_->y()+delta_y_out);
    ++count_outer_;
    count_inner_ = 0;
}

void LosProcessor::Process() {
    double rangesquared = vision_->range()*vision_->range();
    const std::set<int>& relevant_octants = vision_->relevant_octants();

    for(int i = 0; i < 16; ++i)
        preprocessings_[i] = -1;

    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt) {
        switch(*rt) {
            case  1: preprocess( 0, 1); preprocess( 1, 1); preprocess( 1, 1, 1, 0); break;
            case  2: preprocess( 1, 1); preprocess( 1, 0); preprocess( 1, 1, 0, 1); break;
            case  4: preprocess( 1, 0); preprocess( 1,-1); preprocess( 1,-1, 0,-1); break;
            case  5: preprocess( 1,-1); preprocess( 0,-1); preprocess( 1,-1, 1, 0); break;
            case  7: preprocess( 0,-1); preprocess(-1,-1); preprocess(-1,-1,-1, 0); break;
            case  8: preprocess(-1,-1); preprocess(-1, 0); preprocess(-1,-1, 0,-1); break;
            case 10: preprocess(-1, 0); preprocess(-1, 1); preprocess(-1, 1, 0, 1); break;
            case 11: preprocess(-1, 1); preprocess( 0, 1); preprocess(-1, 1,-1, 0); break;
            default: break;
        }
    }


        /* criar cones iniciais */
    /*
        for(auto tt = LosOctant::iterator(*ot);
            ugdk::Vector2D(tt.outer_focus()->x(), tt.outer_focus()->y()).LengthSquared() < rangesquared;
            ++tt) {

            if( ugdk::Vector2D((*tt)->x(),(*tt)->y()).LengthSquared() >= rangesquared)
                tt.jump();
            
            /* comparar com os cones, jogar para vision os tiles visíveis 

        }
        */
}

void LosProcessor::preprocess(int dir_x, int dir_y, int off_x, int off_y) {


}

} // namespace alg
} // namespace game