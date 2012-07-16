
// Header File
#include "game/alg/losprocessor.h"

// External Dependencies
#include <array>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/eqline.h"            // LosCone()
#include "game/base/gamecontroller.h"   // iterator& operator++()
#include "game/base/gameobject.h"       // stuff
#include "game/base/gametile.h"         // focus_, outer_focus_
#include "game/components/vision.h"     // eye()
#include "utils/utils.h"

// Using
using std::array;
using std::list;
using std::map;
using std::set;
using std::tr1::bind;
using std::tr1::function;
using namespace std::tr1::placeholders;
using ugdk::Vector2D;
using game::alg::EqLine;
using game::component::Vision;
using game::base::GameObject;
using game::base::GameTile;
using namespace game::alg::enums;

// Defines
#define PI 3.1415926535897932384626433832795
#define EYE_VEC() Vector2D(static_cast<double>(vision_->eye()->x()),static_cast<double>(vision_->eye()->y()))
#define TILE_VEC(tile) Vector2D(static_cast<double>((tile)->x()),static_cast<double>((tile)->y()))

namespace game {
namespace alg {

LosProcessor::LosProcessor(component::Vision* vision)
  : vision_(vision) {
    for(int i=1; i<=8; ++i)
        octants_[nth_orientation(i)] = new LosOctant(nth_orientation(i),this);
    for(int i=0; i<16; ++i)
        preprocessings_[i] = -1;

    calculate_control_points(vision_->range());
}

LosProcessor::~LosProcessor() {
    for(int i=1; i<=8; ++i)
        if(octants_[nth_orientation(i)] != nullptr) delete octants_[nth_orientation(i)];
    for(auto ct = cones_.begin(); ct != cones_.end(); ++ct)
        if(*ct != nullptr) delete *ct;
}

static int staticcount = 0;

bool LosProcessor::process_cone(const base::GameTile* binded_tile, LosCone* cone) {
    bump::BumpType bt = cone->ComputeBumpType(binded_tile);
    switch(bt) {
        case bump::STP:
            vision_->MarkVisible(binded_tile);
            if(vision_->BlocksVision(binded_tile)) cone->SteepBump(binded_tile);
            return false;
        case bump::MDL:
            vision_->MarkVisible(binded_tile);
            if(vision_->BlocksVision(binded_tile)) {
                ++staticcount;
                if(staticcount < 50) {
                LosCone* newcone = new LosCone(*cone);
                cone->SteepBump(binded_tile);
                newcone->ShallowBump(binded_tile);
                cones_.push_back(newcone);
                }
            }
            return false;
        case bump::BLK:
            vision_->MarkVisible(binded_tile);
            if(vision_->BlocksVision(binded_tile)) return true;
            return false;
        case bump::SHL:
            vision_->MarkVisible(binded_tile);
            if(vision_->BlocksVision(binded_tile)) cone->ShallowBump(binded_tile);
            return false;
        case bump::ABV:
        case bump::BLW:
        default: return false;
    }
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

    Vector2D eye = EYE_VEC();

    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt) {
        EqLine steep(EYE_VEC() + (control_offsets_[*rt])[0], EYE_VEC() + (control_offsets_[*rt])[1]);
        EqLine shallow(EYE_VEC() + (control_offsets_[*rt])[2], EYE_VEC() + (control_offsets_[*rt])[3]);

        //TODO: calcular os blocks preprocessados.
        Vector2D straight_block;
        Vector2D inner_diag_block;
        Vector2D outer_diag_block;

        LosCone* cone_init = new LosCone(steep,shallow,*rt,straight_block,inner_diag_block,outer_diag_block,this);
        cones_.push_back(cone_init);

        for(auto ot = LosOctant::iterator(octants_[*rt],rangesquared);
            (*ot) != nullptr && (TILE_VEC(*ot) - eye).LengthSquared() <= rangesquared;
            ++ot ) {

            staticcount = 0;
            
            //TODO: completar o algoritmo.
            //iterate through the list, removing if necessary.
            function<bool (LosCone*)> process_cone_at_binded_tile = bind( &LosProcessor::process_cone, this, (*ot), _1);
            cones_.remove_if( process_cone_at_binded_tile );

            staticcount = 0;
        
        }
        cones_.clear();
    }
}

void LosProcessor::preprocess(int dir_x, int dir_y, int off_x, int off_y) {
    const base::GameController* gamecontroller = base::GameController::reference();

    bool has_offset = off_x != 0 || off_y != 0;
    GameTile* eye = vision_->eye();
    GameTile* curr_tile = gamecontroller->GetTileFromCoordinates(eye->x()+off_x, eye->y()+off_y);

    if(curr_tile == nullptr) return;

    int count = 0;
    if(has_offset) ++count;

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

        // update stuff for the while condition.
        curr_tile = gamecontroller->GetTileFromCoordinates(curr_tile->x()+dir_x, curr_tile->y()+dir_y);
        ++count;

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
                    preprocessings_[8] = count;
                    break;
                case -1:
                    preprocessings_[0] = count;
                    break;
                default: break;
            } break;
        case  1:
            switch(dir_y) {
                case  0:
                    preprocessings_[4] = count;
                    break;
                case  1:
                    if(off_x == 1) {
                        preprocessings_[5] = count;
                    } else if(off_y == 1) {
                        preprocessings_[7] = count;
                    } else {
                        preprocessings_[6] = count;
                    } break;
                case -1:
                    if(off_x == 1) {
                        preprocessings_[3] = count;
                    } else if(off_y == -1) {
                        preprocessings_[1] = count;
                    } else {
                        preprocessings_[2] = count;
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
                        preprocessings_[11] = count;
                    } else if(off_y == 1) {
                        preprocessings_[9] = count;
                    } else {
                        preprocessings_[10] = count;
                    } break;
                case -1:
                    if(off_x == -1) {
                        preprocessings_[13] = count;
                    } else if(off_y == -1) {
                        preprocessings_[15] = count;
                    } else {
                        preprocessings_[14] = count;
                    } break;
                default: break;
            } break;
        default: break;
    }
}

void LosProcessor::calculate_control_points(double sight_range) {
    Array5Vec2D five_off;

    // first octant.
    five_off[0] = Vector2D(1.0,1.0);
    five_off[1] = Vector2D(1.0,sight_range+1.0);
    five_off[2] = Vector2D(0.0,0.0);
    five_off[3] = Vector2D(sight_range+1.0,0.0);
    five_off[4] = Vector2D(1.0,0.0);
    control_offsets_[1] = five_off;

    // derived octants.
    transform1(control_offsets_[1],2);
    transform2(control_offsets_[2],4);
    transform3(control_offsets_[4],5);
    transform4(control_offsets_[5],7);
    transform1(control_offsets_[7],8);
    transform2(control_offsets_[8],10);
    transform3(control_offsets_[10],11);
}

void LosProcessor::transform1(const Array5Vec2D& base, int dest) {
    Array5Vec2D five_off;
    
    five_off[0] = base[0];
    five_off[1] = base[3];
    five_off[2] = base[2];
    five_off[3] = (base[1] - base[4]).Rotate(-PI/2) + base[4];
    five_off[4] = base[4];

    control_offsets_[dest] = five_off;
}
void LosProcessor::transform2(const Array5Vec2D& base, int dest) {
    Array5Vec2D five_off;
    Vector2D center(0.5,0.5);

    for(int i=0; i<5; ++i) {
        Vector2D tempvec = base[i] - center;
        five_off[i] = Vector2D(tempvec.x,-tempvec.y) + center;
    }
}
void LosProcessor::transform3(const Array5Vec2D& base, int dest) {
    Array5Vec2D five_off;
    
    five_off[0] = base[0];
    five_off[1] = (base[3] - base[4]).Rotate(-PI/2) + base[4];
    five_off[2] = base[2];
    five_off[3] = base[1];
    five_off[4] = base[4];

    control_offsets_[dest] = five_off;
}
void LosProcessor::transform4(const Array5Vec2D& base, int dest) {
    Array5Vec2D five_off;
    Vector2D center(0.5,0.5);

    for(int i=0; i<5; ++i) {
        Vector2D tempvec = base[i] - center;
        five_off[i] = Vector2D(-tempvec.x,tempvec.y) + center;
    }
}

LosOctant::iterator::iterator(const LosOctant* owner, double range_squared)
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

LosOctant::iterator::~iterator() {}

LosOctant::iterator& LosOctant::iterator::operator++() {

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

void LosOctant::iterator::step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    if(count_outer_ <= count_inner_) {
        step_jump(delta_x_out, delta_y_out);
    } else {
        focus_ = gamecontroller->GetTileFromCoordinates(focus_->x()+delta_x_in,focus_->y()+delta_y_in);

        if(focus_ == nullptr || Vector2D(focus_->x() - owner_->owner()->vision()->eye()->x() ,focus_->y() - owner_->owner()->vision()->eye()->y()).LengthSquared() > range_squared_) {
            step_jump(delta_x_out, delta_y_out);
        }
        ++count_inner_;
    }
}

void LosOctant::iterator::step_jump(int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    focus_ = (outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,outer_focus_->y()+delta_y_out) );
    ++count_outer_;
    count_inner_ = 0;
}

LosCone::LosCone(const EqLine& steep, const EqLine& shallow, int octant,
                 const ugdk::Vector2D& straight_block,
                 const ugdk::Vector2D& inner_diag_block, const ugdk::Vector2D& outer_diag_block,
                 const LosProcessor* owner)
  : orientation_(octant), steep_(steep), shallow_(shallow),
    straight_block_(straight_block),
    inner_diag_block_(inner_diag_block), outer_diag_block_(outer_diag_block),
    owner_(owner) {}

bump::BumpType LosCone::ComputeBumpType(const base::GameTile* focus) {
    const Array5Vec2D& offs = owner_->control_offsets().at(orientation_);
    Vector2D foc = TILE_VEC(focus);
    /*
#ifdef DEBUG
    fprintf(stderr,"(%f,%f), (%f,%f)\n",offs[0].x,offs[0].y,offs[2].x,offs[2].y);
#endif
    */
    ord::Ord cmp = steep_.CompareWithVector(foc + offs[0]);
    if( cmp == ord::LT || cmp == ord::EQ )
        return bump::ABV;

    cmp = shallow_.CompareWithVector(foc + offs[2]);
    if( cmp == ord::GT || cmp == ord::EQ )
        return bump::BLW;

    cmp = steep_.CompareWithVector(foc + offs[2]);
    if( cmp == ord::LT ) {
        cmp = shallow_.CompareWithVector(foc + offs[0]);
        if( cmp == ord::GT ) return bump::BLK;
        /* the following compare is useless due to case bump::ABV :
         * cmp = steep_.CompareWithVector(foc + offs[0]);
         * if( cmp == ord::GT || cmp == ord::EQ ) */
        return bump::STP;
    }
    cmp = shallow_.CompareWithVector(foc + offs[0]);
    if( cmp == ord::GT ) return bump::SHL;
    return bump::MDL;
}

#ifdef DEBUG
void LosCone::TestCmpBumpType(const LosProcessor* owner) {
    const base::GameController* gamecontroller = base::GameController::reference();

    EqLine shallow = EqLine(Vector2D(0.0,1.0),Vector2D(40.0,5.0));
    EqLine steep = EqLine(Vector2D(1.0,0.0),Vector2D(5.0,40.0));
    LosCone cone = LosCone(steep,shallow,4,Vector2D(0.0),Vector2D(0.0),Vector2D(0.0),owner);

    GameTile* tile1 = gamecontroller->GetTileFromCoordinates(0,40);
    GameTile* tile2 = gamecontroller->GetTileFromCoordinates(1,5);
    GameTile* tile3 = gamecontroller->GetTileFromCoordinates(30,30);
    GameTile* tile4 = gamecontroller->GetTileFromCoordinates(1,1);
    GameTile* tile5 = gamecontroller->GetTileFromCoordinates(5,1);
    GameTile* tile6 = gamecontroller->GetTileFromCoordinates(40,0);

    fprintf(stderr,"LosCone TestCmpBumpType: %d,",cone.ComputeBumpType(tile1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile2));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile3));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile4));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile5));
    fprintf(stderr,"%d",cone.ComputeBumpType(tile6));
    fprintf(stderr,"\n");
}
#endif

void LosCone::SteepBump(const base::GameTile* tile) {
    Vector2D limit = TILE_VEC(tile) + owner_->control_offsets().at(orientation_)[0];

    steep_.set_target(limit);
    for(auto st = shallow_bumps_.end(); st != shallow_bumps_.begin();) {
        --st;
        if(steep_.CompareWithVector(*st) == ord::LT) {
            steep_.set_origin(*st);
            //TODO: testar essa prox linha em mais detalhe.
            shallow_bumps_.erase(shallow_bumps_.begin(),++st);
            break;
        }
    }
    steep_bumps_.push_back(limit);
}

void LosCone::ShallowBump(const base::GameTile* tile) {
    Vector2D limit = TILE_VEC(tile) + owner_->control_offsets().at(orientation_)[2];

    shallow_.set_target(limit);
    for(auto st = steep_bumps_.end(); st != steep_bumps_.begin();) {
        --st;
        if(shallow_.CompareWithVector(*st) == ord::GT) {
            shallow_.set_origin(*st);
            //TODO: testar essa prox linha em mais detalhe.
            steep_bumps_.erase(steep_bumps_.begin(),++st);
            break;
        }
    }
    shallow_bumps_.push_back(limit);
}

} // namespace alg
} // namespace game