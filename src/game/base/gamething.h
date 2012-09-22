#ifndef BADGAME_BASE_GAMETHING_H_
#define BADGAME_BASE_GAMETHING_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace base {

class GameThing {
  public:
    GameThing(GameObject* obj) : obj_(obj), tile_() {}
    GameThing(const ugdk::math::Integer2D& tile) : obj_(nullptr), tile_(tile) {}
    ~GameThing() {}

    bool is_obj() const { return obj_ != nullptr; }
    const GameObject* obj() const { return obj_; }
          GameObject* obj()       { return obj_; }
    const ugdk::math::Integer2D& tile() const { return tile_; }
          ugdk::math::Integer2D& tile()       { return tile_; }

  private:
    GameObject* obj_;
    ugdk::math::Integer2D tile_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMETHING_H_