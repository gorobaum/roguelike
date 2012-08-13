#ifndef BADGAME_ALG_ODDOCTANTITERATOR_H_
#define BADGAME_ALG_ODDOCTANTITERATOR_H_

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

class OddOctantIterator : public OctantIterator {
  typedef OctantIterator super;

  public:
    OddOctantIterator(double range_squared);
    ~OddOctantIterator() {}

    OddOctantIterator& operator++();

};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_ODDOCTANTITERATOR_H_