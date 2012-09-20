
// Header File
#include "game/alg/los/octantprocessor.h"

// External Dependencies
#include <cassert>
#include <list>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <ugdk/math/frame.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/los/octant.h"
#include "game/alg/equationalline.h"
#include "game/component/vision.h"

// Using
using std::list;
using std::tr1::bind;
using std::tr1::function;
using std::tr1::placeholders::_1;
using ugdk::Frame;
using ugdk::math::Integer2D;
using ugdk::Vector2D;
using namespace game::alg::los::enums;
using game::alg::EquationalLine;
using game::component::Vision;

namespace game {
namespace alg {
namespace los {

OctantProcessor::OctantProcessor(int octant_id, Vision* vision)
  : octant_(octant_id, vision->range()*vision->range()), vision_(vision) {
    cone_processor_ = bind( &OctantProcessor::process_cone_here, this, _1 );
}

OctantProcessor::~OctantProcessor() { clean_cones(); }

void OctantProcessor::ProcessOctant() {
    double range = vision_->range() + 1.0;
    Frame eye = vision_->eye_frame();

	// Reset the octant.
    octant_.set_origin(vision_->eye_coords()); 
	octant_.iterator()->Reset();

    // Setup the startup cones.
    EquationalLineDouble upper_line( Vector2D(eye.right(), eye.bottom()), Vector2D(eye.right(),   -range ) );
	EquationalLineDouble lower_line( Vector2D(eye.left() , eye.top()   ), Vector2D(      range, eye.top()) );

	Cone* startup_cone = new Cone(upper_line,lower_line);
	cones_.push_back(startup_cone);

    // Iterate through the octant.
    while(!octant_.iterator()->end()) {

        if(!octant_.FocusIsOutOfBounds()) {
            // iterate through the cone list, verifying the current focused tile.
            cones_.remove_if( cone_processor_ );
        }

        ++*(octant_.iterator());
    }
    clean_cones();
}

bool OctantProcessor::process_cone_here(Cone* cone) {
    // Get the stuffs.
    Integer2D fake_coords = octant_.FakeCoordinates();
    Integer2D focus_tile = octant_.FocusCoordinates();

    // First analyse how this tile relates to this cone.
    bump::BumpType bt = cone->ComputeBumpType(fake_coords);

    // If the cone intersects with it, it is visible.
    if( bt != bump::ABV && bt != bump::BLW )
		if( !octant_.FocusIsControlTile() )
			vision_->MarkVisible(focus_tile);

    // If it doesn't block the vision, then we move on and keep the cone alive.
    if(!vision_->BlocksVision(focus_tile))
        return false;

    // Otherwise,
    Cone* newcone = nullptr;
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
            newcone = new Cone(*cone); 
            cone->UpperBump(fake_coords);
            newcone->LowerBump(fake_coords);
            cones_.push_back(newcone);
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
