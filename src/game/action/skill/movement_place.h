#ifndef ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_
#define ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_

// Inheritance
#include "game/action/skill/movement.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {
namespace skill {

class MovementPlace : public Movement {
  typedef Movement super;
  public:
    MovementPlace();
    ~MovementPlace();

};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_