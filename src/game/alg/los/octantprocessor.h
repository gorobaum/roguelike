#ifndef ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_
#define ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/alg/los/octant.h"
#include "game/alg/los/cone.h"

// Forward Declarations
#include "game/alg.h"
#include "game/component.h"

namespace game {
namespace alg {
namespace los {

class OctantProcessor {
  public:
    OctantProcessor(int octant_id, component::Vision* vision);
    ~OctantProcessor();

    void ProcessOctant();

	void set_origin(const ugdk::math::Integer2D& origin) { octant_.set_origin(origin); }

  private:
    bool process_cone_here(Cone* cone);
    void clean_cones();

    Octant octant_;
    std::list<Cone*> cones_;
    component::Vision* vision_;

	std::tr1::function<bool (Cone*)> cone_processor_; // process_cone_here's incarnation as a non-method function.
};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_OCTANTPROCESSOR_H_