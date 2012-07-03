
// Header File
#include "game/alg/losprocessor.h"

// External Dependencies
#include <list>
#include <set>

// Internal Dependencies
#include "game/base/gamecontroller.h"   // iterator& operator++()
#include "game/base/gameobject.h"       // stuff
#include "game/base/gametile.h"         // focus_, outer_focus_
#include "game/components/vision.h"     // eye()

// Using
using std::list;
using std::set;
using ugdk::Vector2D;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace alg {

LosProcessor::LosProcessor(component::Vision* vision)
  : vision_(vision), octants_(12), preprocessings_(16,-1) {
    for(int i = 1; i <= 8; ++i)
        octants_[nth_orientation(i)] = new LosOctant(nth_orientation(i),this);
}

LosProcessor::~LosProcessor() {
    for(auto ot = octants_.begin(); ot != octants_.end(); ++ot)
        if(*ot != nullptr) delete *ot;
}

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

    GameTile* eye = owner->owner()->vision()->eye();

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
        if(focus_ == nullptr) {
            focus_ = outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,outer_focus_->y()+delta_y_out);
            ++count_outer_;
            count_inner_ = 0;
        }
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
    double rangesquared = vision_->range();
    rangesquared *= rangesquared;
    const set<int>& relevant_octants = vision_->relevant_octants();

    //TODO: process gameobject tiles.

    // clear the preprocessings vector.
    for(int i = 0; i < 16; ++i)
        preprocessings_[i] = -1;

    // preprocess stuff.
    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt) {
        switch(*rt) {
            case  1: preprocess( 0,-1); preprocess( 1,-1); preprocess( 1,-1, 1, 0); break;
            case  2: preprocess( 1,-1); preprocess( 1, 0); preprocess( 1,-1, 0,-1); break;
            case  4: preprocess( 1, 0); preprocess( 1, 1); preprocess( 1, 1, 0, 1); break;
            case  5: preprocess( 1, 1); preprocess( 0, 1); preprocess( 1, 1, 1, 0); break;
            case  7: preprocess( 0, 1); preprocess(-1, 1); preprocess(-1, 1,-1, 0); break;
            case  8: preprocess(-1, 1); preprocess(-1, 0); preprocess(-1, 1, 0, 1); break;
            case 10: preprocess(-1, 0); preprocess(-1,-1); preprocess(-1,-1, 0,-1); break;
            case 11: preprocess(-1,-1); preprocess( 0,-1); preprocess(-1,-1,-1, 0); break;
            default: break;
        }
    }
    /* criar cones iniciais */

    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt) {
        for(auto ot = LosOctant::iterator(octants_[*rt]); (*ot) != nullptr;  ++ot) {
            
            if(Vector2D((*ot)->x() - vision_->eye()->x(), (*ot)->y() - vision_->eye()->y()).LengthSquared() > rangesquared) {
                ot.jump();
                if(*ot == nullptr) break;
                if(Vector2D((*ot)->x() - vision_->eye()->x(), (*ot)->y() - vision_->eye()->y()).LengthSquared() > rangesquared) break;
            }

            vision_->MarkVisible(*ot);

        }

    }


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
    const base::GameController* gamecontroller = base::GameController::reference();

    bool has_offset = off_x != 0 || off_y != 0;
    GameTile* eye = vision_->eye();
    GameTile* curr_tile = gamecontroller->GetTileFromCoordinates(eye->x()+off_x+dir_x, eye->y()+off_y+dir_y);

    if(curr_tile == nullptr) return;

    int count = 0;

    // uuuugh lots of squared values...
    double rangesq = vision_->range();
    rangesq *= rangesq;
    double dxsq = curr_tile->x() - eye->x();
    dxsq *= dxsq;
    double dysq = curr_tile->y() - eye->y();
    dysq *= dysq;
    double distsq = dxsq + dysq;

    // here, here's the main loop.
    while(distsq <= rangesq) {
        if(!has_offset) vision_->MarkVisible(curr_tile);

        if(vision_->BlocksVision(curr_tile)) break;

        ++count;

        // update stuff for the while condition.
        curr_tile = gamecontroller->GetTileFromCoordinates(curr_tile->x()+dir_x, curr_tile->y()+dir_y);
        

        // can't look beyond the universe, yo!
        if(curr_tile == nullptr) break;

        dxsq = curr_tile->x() - eye->x();
        dxsq *= dxsq;
        dysq = curr_tile->y() - eye->y();
        dysq *= dysq;
        distsq = dxsq + dysq;
    }

    // if exited from range condition, or map limits, we're done!
    if(distsq > rangesq || curr_tile == nullptr) return;

    // otherwise, store the count in the correct position in the preprocessings_ vector...
    // ...the correct.. position... HHHHNNNNNGGGGGGFFFSSS
    switch(dir_x) {
        case  0:
            switch(dir_y) {
                case  1:
                    preprocessings_[0] = count;
                    break;
                case -1:
                    preprocessings_[8] = count;
                    break;
                default: break;
            }
        case  1:
            switch(dir_y) {
                case  0:
                    preprocessings_[4] = count;
                    break;
                case  1:
                    if(off_x == 1) {
                        preprocessings_[3] = count;
                    } else if(off_y == 1) {
                        preprocessings_[1] = count;
                    } else {
                        preprocessings_[2] = count;
                    } break;
                case -1:
                    if(off_x == 1) {
                        preprocessings_[5] = count;
                    } else if(off_y == -1) {
                        preprocessings_[7] = count;
                    } else {
                        preprocessings_[6] = count;
                    } break;
                default: break;
            } break;
        case -1:
            switch(dir_y) {
                case  0:
                    preprocessings_[12] = count;
                    break;
                case  1:
                    if(off_x == -1) {
                        preprocessings_[13] = count;
                    } else if(off_y == 1) {
                        preprocessings_[15] = count;
                    } else {
                        preprocessings_[14] = count;
                    } break;
                case -1:
                    if(off_x == -1) {
                        preprocessings_[11] = count;
                    } else if(off_y == -1) {
                        preprocessings_[9] = count;
                    } else {
                        preprocessings_[10] = count;
                    } break;
                default: break;
            } break;
        default: break;
    }
}

} // namespace alg
} // namespace game