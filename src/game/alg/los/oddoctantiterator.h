#ifndef BADGAME_ALG_LOS_ODDOCTANTITERATOR_H_
#define BADGAME_ALG_LOS_ODDOCTANTITERATOR_H_

// Inheritance
#include "game/alg/los/octantiterator.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace alg {
namespace los {

class OddOctantIterator : public OctantIterator {
  typedef OctantIterator super;

  public:
    OddOctantIterator(double range_squared);
    ~OddOctantIterator() {}

    OddOctantIterator& operator++();
    void reset();

};

} // namespace los
} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOS_ODDOCTANTITERATOR_H_