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
    OctantIterator(double range_squared) : range_squared_(range_squared), focus_(0), outer(0) {}
    ~OctantIterator();

    ugdk::math::Integer2D operator*() const { return focus_; }
    const std::list<game::base::GameObject*>& objects_at_focus() const { return objects_at_focus_; }
    virtual OctantIterator& operator++() = 0;

  private:
    double range_squared_;
    ugdk::math::Integer2D focus_;
    ugdk::math::Integer2D outer_;
    const std::list<game::base::GameObject*>& objects_at_focus_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_OCTANTITERATOR_H_