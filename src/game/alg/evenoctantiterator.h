#ifndef BADGAME_ALG_EVENOCTANTITERATOR_H_
#define BADGAME_ALG_EVENOCTANTITERATOR_H_

// Inheritance
#include "game/alg/octantiterator.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace alg {

class EvenOctantIterator : public OctantIterator {
  typedef OctantIterator super;

  public:
    EvenOctantIterator(double range_squared);
    ~EvenOctantIterator() {}

    EvenOctantIterator& operator++();

};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EVENOCTANTITERATOR_H_