#ifndef BADGAME_ALG_LOSOCTANT_H_
#define BADGAME_ALG_LOSOCTANT_H_

// Inheritance
// (none)

// External Dependencies
#include <list>

// Internal Dependencies
#include "game/alg/octantiterator.h"

// Forward Declarations
#include "game/base.h"
#include "game/alg.h"

namespace game {
namespace alg {

class LoSOctant {
  // lacks operator=
  LoSOctant& operator=(const LoSOctant&);

  public:
    LoSOctant(int id, double range_squared);
    ~LoSOctant();

    bool OutOfBounds(const ugdk::math::Integer2D& coords) const;
    std::list<base::GameObject*>& ObjectsAtFocus() const;

    LoSOctant& operator++() { ++(*iterator_); return *this; }

  private:
    const int rotations_;
    OctantIterator* iterator_;

};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSOCTANT_H_