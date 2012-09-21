#ifndef ROGUELIKE_ALG_LOS_ODDOCTANTITERATOR_H_
#define ROGUELIKE_ALG_LOS_ODDOCTANTITERATOR_H_

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
    void Reset();
	bool FocusIsControlTile() const;

};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_ODDOCTANTITERATOR_H_