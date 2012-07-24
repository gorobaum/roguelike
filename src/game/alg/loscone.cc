
// Header File
#include "game/alg/loscone.h"

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/losprocessor.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"
#include "utils/utils.h"

// Using
using ugdk::Vector2D;
using namespace game::alg::enums;
using game::base::GameTile;
using namespace utils::enums;

// Defines
#define TILE_VEC(tile) Vector2D(static_cast<double>((tile)->x()),static_cast<double>((tile)->y()))

namespace game {
namespace alg {

LoSCone::LoSCone(const EqLine& steep, const EqLine& shallow, int octant,
                 const LoSProcessor* owner)
  : orientation_(octant), steep_(steep), shallow_(shallow),
    owner_(owner) {}

bump::BumpType LoSCone::ComputeBumpType(const base::GameTile* focus, int ydir) {
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
void LoSCone::TestCmpBumpType(const LoSProcessor* owner) {
    const base::GameController* gamecontroller = base::GameController::reference();

    EqLine shallow = EqLine(Vector2D(0.0,1.0),Vector2D(40.0,5.0));
    EqLine steep = EqLine(Vector2D(1.0,0.0),Vector2D(5.0,40.0));
    LoSCone cone = LoSCone(steep,shallow,4,owner);

    GameTile* tile1 = gamecontroller->GetTileFromCoordinates(0,40);
    GameTile* tile2 = gamecontroller->GetTileFromCoordinates(1,5);
    GameTile* tile3 = gamecontroller->GetTileFromCoordinates(30,30);
    GameTile* tile4 = gamecontroller->GetTileFromCoordinates(1,1);
    GameTile* tile5 = gamecontroller->GetTileFromCoordinates(5,1);
    GameTile* tile6 = gamecontroller->GetTileFromCoordinates(40,0);

    fprintf(stderr,"LoSCone TestCmpBumpType: %d,",cone.ComputeBumpType(tile1,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile2,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile3,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile4,1));
    fprintf(stderr,"%d,",cone.ComputeBumpType(tile5,1));
    fprintf(stderr,"%d",cone.ComputeBumpType(tile6,1));
    fprintf(stderr,"\n");
}
#endif

void LoSCone::SteepBump(const base::GameTile* tile, int ydir) {
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

void LoSCone::ShallowBump(const base::GameTile* tile, int ydir) {
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
