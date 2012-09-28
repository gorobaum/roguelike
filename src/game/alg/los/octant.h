#ifndef ROGUELIKE_ALG_LOS_OCTANT_H_
#define ROGUELIKE_ALG_LOS_OCTANT_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/alg/los/octantiterator.h"

// Forward Declarations
#include "game/alg.h"

namespace game {
namespace alg {
namespace los {

class Octant {
  // lacks operator=
  Octant& operator=(const Octant&);

  public:
    Octant(int id, double range_squared);
    ~Octant();

    ugdk::math::Integer2D FocusCoordinates() const;
    ugdk::math::Integer2D FakeCoordinates() const { return **iterator_; }
    
    bool FocusIsOutOfBounds() const;
	bool FocusIsControlTile() const;

    OctantIterator* iterator() { return iterator_; }
    
    int    parity() const { return    parity_; }
    int rotations() const { return rotations_; }

    void set_origin(const ugdk::math::Integer2D& origin) { origin_ = origin; }

  private:
    const int parity_;
    const int rotations_;
    ugdk::math::Integer2D origin_;
    OctantIterator* iterator_;

};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_OCTANT_H_