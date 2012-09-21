#ifndef ROGUELIKE_ALG_LOS_EVENOCTANTITERATOR_H_
#define ROGUELIKE_ALG_LOS_EVENOCTANTITERATOR_H_

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

class EvenOctantIterator : public OctantIterator {
  typedef OctantIterator super;

  public:
    EvenOctantIterator(double range_squared);
    ~EvenOctantIterator() {}

    EvenOctantIterator& operator++();
    void Reset();
	bool FocusIsControlTile() const;

};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_EVENOCTANTITERATOR_H_