
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

bool LosProcessor::process_cone(const base::GameTile* binded_tile, LosCone* cone) {
    int ydir = -1;
    if(cone->orientation() >= 4 && cone->orientation() <= 8) ydir = 1; 

    bump::BumpType bt = cone->ComputeBumpType(binded_tile,ydir);
    LosCone* newcone = nullptr;

    if( bt != bump::ABV && bt != bump::BLW )
        vision_->MarkVisible(binded_tile);

    if(!vision_->BlocksVision(binded_tile))
        return false;
    
    switch(bt) {
        case bump::BLK:
            return true;
        case bump::STP:
            cone->SteepBump(binded_tile,ydir);
            break;
        case bump::SHL:
            cone->ShallowBump(binded_tile,ydir);
            break;
        case bump::MDL:
            newcone = new LosCone(*cone);
            cone->SteepBump(binded_tile,ydir);
            newcone->ShallowBump(binded_tile,ydir);
            cones_.push_back(newcone);
            break;
        case bump::ABV:
        case bump::BLW:
        default: break;
    }
    return false;
}

void LosProcessor::Process() {
    const base::GameController* gamecontroller = base::GameController::reference();

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

    GameTile* eye = vision_->eye();
    Vector2D eyev = TILE_VEC(eye);

    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt) {
        
        Vector2D anti_vert_offset(0.0);
        if( (*rt) == 1 || (*rt) ==  5 ) { anti_vert_offset.x = -0.000001; }
        if( (*rt) == 7 || (*rt) == 11 ) { anti_vert_offset.x =  0.000001; }

        EqLine steep(eyev + control_offsets_[*rt][0] + anti_vert_offset, eyev + control_offsets_[*rt][1]);
        EqLine shallow(eyev + control_offsets_[*rt][2], eyev + control_offsets_[*rt][3]);
        EqLine aux_steep(eyev + control_offsets_[*rt][5] , eyev + control_offsets_[*rt][6]);
        EqLine aux_shallow(eyev + control_offsets_[*rt][7] , eyev + control_offsets_[*rt][8]);

        //TODO: calcular as ids dos preprocessados.
        int straight_p;
        int inner_diag_p;
        int outer_diag_p;

        switch(*rt) {
            case  1: straight_p =  0; inner_diag_p =  2; outer_diag_p =  3; break;
            case  2: straight_p =  4; inner_diag_p =  2; outer_diag_p =  1; break;
            case  4: straight_p =  4; inner_diag_p =  6; outer_diag_p =  7; break;
            case  5: straight_p =  8; inner_diag_p =  6; outer_diag_p =  5; break;
            case  7: straight_p =  8; inner_diag_p = 10; outer_diag_p = 11; break;
            case  8: straight_p = 12; inner_diag_p = 10; outer_diag_p =  9; break;
            case 10: straight_p = 12; inner_diag_p = 14; outer_diag_p = 15; break;
            case 11: straight_p =  0; inner_diag_p = 14; outer_diag_p = 13; break;
            default: straight_p =  0; inner_diag_p =  0; outer_diag_p =  0;break;
        }

        LosCone* cone_init_main = new LosCone(steep,shallow,*rt,this);
        LosCone* cone_init_aux = new LosCone(aux_steep,aux_shallow,*rt,this);

        cones_.push_back(cone_init_main);
        cones_.push_back(cone_init_aux);

        for(auto ot = LosOctant::iterator(octants_[*rt],rangesquared);
            (*ot) != nullptr && (TILE_VEC(*ot) - eyev).LengthSquared() <= rangesquared;
            ++ot ) {
               /*
            // we need to feed the preprocessings to the cones' bump lists as they become relevant:
            if( ot.count_outer() == preprocessings_[straight_p] - 1 && ot.count_inner() == 0 ) {
                // straight preprocess:
                if( straight_p % 8 == 0 ) {
                    int straightdir = -1;
                    if( straight_p != 0 ) straightdir = 1;

                    GameTile* straight_b = gamecontroller->GetTileFromCoordinates(
                                               eye->x(),
                                               eye->y() + straightdir*preprocessings_[straight_p]
                                           );

                    for(auto ct = cones_.begin(); ct != cones_.end(); ++ct) {
                        int ydir = -1;
                        if((*ct)->orientation() >= 4 && (*ct)->orientation() <= 8) ydir = 1;

                        bump::BumpType bmp = (*ct)->ComputeBumpType(straight_b,ydir);
                        if( bmp != bump::ABV && bmp != bump::BLW )
                            (*ct)->SteepBump(straight_b,ydir);
                    }

                } else {
                    int straightdir = 1;
                    if( straight_p != 4 ) straightdir = -1;

                    GameTile* straight_b = gamecontroller->GetTileFromCoordinates(
                                               eye->x() + straightdir*preprocessings_[straight_p],
                                               eye->y()
                                           );

                    for(auto ct = cones_.begin(); ct != cones_.end(); ++ct) {
                        int ydir = -1;
                        if((*ct)->orientation() >= 4 && (*ct)->orientation() <= 8) ydir = 1;

                        bump::BumpType bmp = (*ct)->ComputeBumpType(straight_b,ydir);
                        if( bmp != bump::ABV && bmp != bump::BLW )
                            (*ct)->ShallowBump(straight_b,ydir);
                    }

                }
            }
            */

            // iterate through the list, removing if necessary.
            function<bool (LosCone*)> process_cone_at_binded_tile = bind( &LosProcessor::process_cone, this, (*ot), _1);
            cones_.remove_if( process_cone_at_binded_tile );
        
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
    Array9Vec2D nine_off;
    sight_range *= 2.0;

    // first octant.
    nine_off[0] = Vector2D(1.0,1.0);                       // steep near offset
    nine_off[1] = Vector2D(1.0,-sight_range);              // steep far offset
    nine_off[2] = Vector2D(0.0,0.0);                       // shallow near offset
    nine_off[3] = Vector2D(sight_range+1.0,-sight_range);  // shallow far offset

    nine_off[4] = Vector2D(1.0,0.0);                       // rotate center

    nine_off[5] = nine_off[0];                             // aux steep near offset
    nine_off[6] = Vector2D(2.0,-2.0);                      // aux steep far offset
    nine_off[7] = Vector2D(0.0,1.0);                       // aux shallow near offset
    nine_off[8] = nine_off[3];                             // aux shallow far offset

    control_offsets_[1] = Array9Vec2D(nine_off);

    // derived octants.
    transform1(control_offsets_[1],2);
    transform2(control_offsets_[2],4);
    transform3(control_offsets_[4],5);
    transform4(control_offsets_[5],7);
    transform1(control_offsets_[7],8);
    transform2(control_offsets_[8],10);
    transform3(control_offsets_[10],11);
}

void LosProcessor::transform1(const Array9Vec2D& base, int dest) {
    Array9Vec2D nine_off;
    
    nine_off[0] = base[0];
    nine_off[1] = base[3];
    nine_off[2] = base[2];
    Vector2D tempvec = base[1] - base[4];
    nine_off[3] = Vector2D(-tempvec.y,-tempvec.x) + base[4];

    nine_off[4] = base[4];

    nine_off[5] = base[7];
    nine_off[6] = base[8];
    tempvec = base[5] - base[4];
    nine_off[7] = Vector2D(-tempvec.y,-tempvec.x) + base[4];
    tempvec = base[6] - base[4];
    nine_off[8] = Vector2D(-tempvec.y,-tempvec.x) + base[4];

    control_offsets_[dest] = Array9Vec2D(nine_off);
}
void LosProcessor::transform2(const Array9Vec2D& base, int dest) {
    Array9Vec2D nine_off;
    Vector2D center(0.5,0.5);

    for(int i=0; i<9; ++i) {
        Vector2D tempvec = base[i] - center;
        nine_off[i] = Vector2D(tempvec.x,-tempvec.y) + center;
    }

    control_offsets_[dest] = Array9Vec2D(nine_off);
}
void LosProcessor::transform3(const Array9Vec2D& base, int dest) {
    Array9Vec2D nine_off;
    
    nine_off[0] = base[0];
    Vector2D tempvec = base[3] - base[4];
    nine_off[1] = Vector2D(tempvec.y,tempvec.x) + base[4];
    nine_off[2] = base[2];
    nine_off[3] = base[1];

    nine_off[4] = base[4];
    
    tempvec = base[7] - base[4];
    nine_off[5] = Vector2D(tempvec.y,tempvec.x) + base[4];
    tempvec = base[8] - base[4];
    nine_off[6] = Vector2D(tempvec.y,tempvec.x) + base[4];
    nine_off[7] = base[5];
    nine_off[8] = base[6];

    control_offsets_[dest] = Array9Vec2D(nine_off);
}
void LosProcessor::transform4(const Array9Vec2D& base, int dest) {
    Array9Vec2D nine_off;
    Vector2D center(0.5,0.5);

    for(int i=0; i<9; ++i) {
        Vector2D tempvec = base[i] - center;
        nine_off[i] = Vector2D(-tempvec.x,tempvec.y) + center;
    }
    
    control_offsets_[dest] = Array9Vec2D(nine_off);
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

        if(focus_ == nullptr
           || Vector2D(focus_->x() - owner_->owner()->vision()->eye()->x() ,
                       focus_->y() - owner_->owner()->vision()->eye()->y()).LengthSquared() > range_squared_) {

            step_jump(delta_x_out, delta_y_out);
        }
        ++count_inner_;
    }
}

void LosOctant::iterator::step_jump(int delta_x_out, int delta_y_out) {
    const base::GameController* gamecontroller = base::GameController::reference();

    focus_ = (outer_focus_ = gamecontroller->GetTileFromCoordinates(outer_focus_->x()+delta_x_out,
                                                                    outer_focus_->y()+delta_y_out) );
    ++count_outer_;
    count_inner_ = 0;
}

LosCone::LosCone(const EqLine& steep, const EqLine& shallow, int octant,
                 const LosProcessor* owner)
  : orientation_(octant), steep_(steep), shallow_(shallow),
    owner_(owner) {}

bump::BumpType LosCone::ComputeBumpType(const base::GameTile* focus, int ydir) {
    const Array9Vec2D& offs = owner_->control_offsets().at(orientation_);
    Vector2D foc = TILE_VEC(focus);
    /*
#ifdef DEBUG
    fprintf(stderr,"(%f,%f), (%f,%f)\n",offs[0].x,offs[0].y,offs[2].x,offs[2].y);
#endif
    */
    ord::Ord cmp = steep_.CompareWithVector(foc + offs[0]);
    if(ydir == -1) {
        if( cmp == ord::GT || cmp == ord::EQ )
            return bump::ABV;

        cmp = shallow_.CompareWithVector(foc + offs[2]);
        if( cmp == ord::LT || cmp == ord::EQ )
            return bump::BLW;

        cmp = steep_.CompareWithVector(foc + offs[2]);
        if( cmp == ord::GT ) {
            cmp = shallow_.CompareWithVector(foc + offs[0]);
            if( cmp == ord::LT ) return bump::BLK;
            /* the following compare is useless due to case bump::ABV :
             * cmp = steep_.CompareWithVector(foc + offs[0]);
             * if( cmp == ord::LT || cmp == ord::EQ ) */
            return bump::STP;
        }
        cmp = shallow_.CompareWithVector(foc + offs[0]);
        if( cmp == ord::LT ) return bump::SHL;
    } else {
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
    }
    return bump::MDL;
}

#ifdef DEBUG
void LosCone::TestCmpBumpType(const LosProcessor* owner) {
    const base::GameController* gamecontroller = base::GameController::reference();

    EqLine shallow = EqLine(Vector2D(0.0,1.0),Vector2D(40.0,5.0));
    EqLine steep = EqLine(Vector2D(1.0,0.0),Vector2D(5.0,40.0));
    LosCone cone = LosCone(steep,shallow,4,owner);

    GameTile* tile1 = gamecontroller->GetTileFromCoordinates(0,40);
    GameTile* tile2 = gamecontroller->GetTileFromCoordinates(1,5);
    GameTile* tile3 = gamecontroller->GetTileFromCoordinates(30,30);
    GameTile* tile4 = gamecontroller->GetTileFromCoordinates(1,1);
    GameTile* tile5 = gamecontroller->GetTileFromCoordinates(5,1);
    GameTile* tile6 = gamecontroller->GetTileFromCoordinates(40,0);

    fprintf(stderr,"LosCone TestCmpBumpType: %d,",cone.ComputeBumpType(tile1,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile2,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile3,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile4,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile5,1));
    fprintf(stderr,"%d",cone.ComputeBumpType(tile6,1));
    fprintf(stderr,"\n");
}
#endif

void LosCone::SteepBump(const base::GameTile* tile, int ydir) {
    Vector2D limit = TILE_VEC(tile) + owner_->control_offsets().at(orientation_)[0];

    steep_.set_target(limit);
    for(auto st = shallow_bumps_.end(); st != shallow_bumps_.begin();) {
        --st;
        if( (ydir == -1 && steep_.CompareWithVector(*st) == ord::GT) 
            || (ydir == 1 && steep_.CompareWithVector(*st) == ord::LT) ) {
            steep_.set_origin(*st);
            //TODO: testar essa prox linha em mais detalhe.
            //shallow_bumps_.erase(shallow_bumps_.begin(),++st);
            break;
        }
    }
    steep_bumps_.push_back(limit);
}

void LosCone::ShallowBump(const base::GameTile* tile, int ydir) {
    Vector2D limit = TILE_VEC(tile) + owner_->control_offsets().at(orientation_)[2];

    shallow_.set_target(limit);
    for(auto st = steep_bumps_.end(); st != steep_bumps_.begin();) {
        --st;
        if( (ydir == -1 && shallow_.CompareWithVector(*st) == ord::LT)
            || (ydir == 1 && shallow_.CompareWithVector(*st) == ord::GT) ) {
            shallow_.set_origin(*st);
            //TODO: testar essa prox linha em mais detalhe.
            //steep_bumps_.erase(steep_bumps_.begin(),++st);
            break;
        }
    }
    shallow_bumps_.push_back(limit);
}

} // namespace alg
} // namespace game