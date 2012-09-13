
// Header File
#include "game/alg/los/octantprocessor.h"

// External Dependencies
#include <cassert>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <list>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/alg/los/octant.h"
#include "game/alg/equationalline.h"
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/vision.h"

// Using
using std::list;
using std::tr1::bind;
using std::tr1::function;
using std::tr1::placeholders::_1;
using ugdk::math::Integer2D;
using namespace game::alg::los::enums;
using game::alg::EquationalLine;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using game::component::Vision;

namespace game {
namespace alg {
namespace los {

OctantProcessor::OctantProcessor(int octant_id, Vision* vision)
  : octant_(octant_id, vision->range()*vision->range()), vision_(vision) {}

OctantProcessor::~OctantProcessor() { clean_cones(); }

void OctantProcessor::ProcessOctant() {

    int int_range = static_cast<int>(vision_->range()) + 1;

    octant_.set_origin(vision_->eye());

    Cone* upper_cone = nullptr;
    Cone* lower_cone = nullptr;

    // Setup the startup cones.
    if( octant_.parity() == 0 ) {
        EquationalLine upper_upper(Integer2D(1,1), Integer2D(1,-int_range));
        EquationalLine upper_lower(Integer2D(0,0), Integer2D(int_range+1, -int_range));

        EquationalLine lower_upper(Integer2D(1,1), Integer2D(2,-2));
        EquationalLine lower_lower(Integer2D(0,1), Integer2D(int_range+1, -int_range));

        upper_cone = new Cone(upper_upper,upper_lower);
        lower_cone = new Cone(lower_upper,lower_lower);
    } else {
        EquationalLine upper_upper(Integer2D(0,1), Integer2D(int_range+1, -int_range));
        EquationalLine upper_lower(Integer2D(0,0), Integer2D(2,-1));

        EquationalLine lower_upper(Integer2D(1,1), Integer2D(int_range+1, -int_range));
        EquationalLine lower_lower(Integer2D(0,0), Integer2D(int_range, 0));
        
        upper_cone = new Cone(upper_upper,upper_lower);
        lower_cone = new Cone(lower_upper,lower_lower);
    }

    cones_.push_back(upper_cone);
    cones_.push_back(lower_cone);

    // Iterate through the octant.
    while(!octant_.iterator()->end()) {

        if(!octant_.FocusIsOutOfBounds()) {
            // iterate through the cone list, verifying the current focused tile.
            function<bool (Cone*)> predicate = bind( &OctantProcessor::process_cone_here, this, _1 );
            cones_.remove_if( predicate );
        }

        ++*(octant_.iterator());
    }
    clean_cones();
}

bool OctantProcessor::process_cone_here(Cone* cone) {
    const GameController* gamecontroller = GameController::reference();

    Integer2D fake_coords = octant_.FakeCoordinates();
    GameTile* focus_tile = gamecontroller->GetTileFromCoordinates(octant_.FocusCoordinates());

    // First analyse how this tile relates to this cone.
    bump::BumpType bt = cone->ComputeBumpType(fake_coords);

    // If the cone intersects with it, it is visible.
    if( bt != bump::ABV && bt != bump::BLW )
        vision_->MarkVisible(focus_tile);

    // If it doesn't block the vision, then we move on and keep the cone alive.
    if(!vision_->BlocksVision(focus_tile))
        return false;

    // Otherwise,
    //Cone* newcone;
    switch(bt) {
        case bump::BLK: // do nothing and kill this cone.
            return true;
        case bump::UPR: // do an upper bump.
            cone->UpperBump(fake_coords);
            break;
        case bump::LWR: // do a lower bump.
            cone->LowerBump(fake_coords);
            break;
        case bump::MDL: // split the cone in two, and make an upper bump and a lower bump respectively.
            //newcone = new Cone(*cone); 
            cone->UpperBump(fake_coords);
            //newcone->LowerBump(fake_coords);
            //cones_.push_back(newcone);
            break;
        case bump::ABV: // ignore these cases
        case bump::BLW: break;
        default: assert(false); break;
    }
    return false;
}

void OctantProcessor::clean_cones() {
    for( auto ct = cones_.begin(); ct != cones_.end(); ++ct )
        delete (*ct);
    cones_.clear();
}

} // namespace los
} // namespace alg
} // namespace game
