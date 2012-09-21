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
  private:
    bool is_obj_;
    union {
        GameObject* obj_;  
        ugdk::math::Integer2D* tile_;
    } it_;

  public:
    GameThing(GameObject* obj) : is_obj_(true) {
        it_.obj_ = obj;
    }
    GameThing(const ugdk::math::Integer2D& tile) : is_obj_(false) {
        it_.tile_ = new ugdk::math::Integer2D(tile);
    }
    ~GameThing() { if(!is_obj_) delete it_.tile_; }

    bool is_obj() { return is_obj_; }
    const GameObject* obj() const { return it_.obj_; }
          GameObject* obj()       { return it_.obj_; }
    const ugdk::math::Integer2D& tile() const { return *it_.tile_; }
          ugdk::math::Integer2D& tile()       { return *it_.tile_; }
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMETHING_H_