﻿#ifndef BADGAME_ALG_LOS_OCTANT_H_
#define BADGAME_ALG_LOS_OCTANT_H_

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
    bool FocusIsOutOfBounds() const;
    ugdk::math::Integer2D FakeCoordinates() const { return **iterator_; }
	const ugdk::math::Integer2D& straight_dir() const { return straight_dir_; }

    int parity() const { return parity_; }
    OctantIterator* iterator() { return iterator_; }

    void set_origin(const ugdk::math::Integer2D& origin) { origin_ = origin; }

  private:
    const int parity_;
    const int rotations_;
	const ugdk::math::Integer2D straight_dir_;
    ugdk::math::Integer2D origin_;
    OctantIterator* iterator_;

};

} // namespace los
} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOS_OCTANT_H_