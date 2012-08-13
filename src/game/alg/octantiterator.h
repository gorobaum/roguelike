#ifndef BADGAME_ALG_OCTANTITERATOR_H_
#define BADGAME_ALG_OCTANTITERATOR_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace alg {

class OctantIterator {
  public:
    OctantIterator(double range_squared, const ugdk::math::Integer2D& start_offset )
      : range_squared_(range_squared), focus_(start_offset) {}
    ~OctantIterator() {}

    ugdk::math::Integer2D operator*() const { return focus_; }
    bool end() const { return focus_.x*focus_.x + focus_.y*focus_.y > range_squared_; }
    virtual OctantIterator& operator++() = 0;

  protected:
    double range_squared_;
    ugdk::math::Integer2D focus_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_OCTANTITERATOR_H_