#ifndef ROGUELIKE_ACTION_SKILL_MOVEMENT_STEP_H_
#define ROGUELIKE_ACTION_SKILL_MOVEMENT_STEP_H_

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

class MovementStep : public Movement {
  typedef Movement super;
  public:
    static Skill& reference() { return reference_ == nullptr ? *(new MovementStep) : *reference_; }
    ~MovementStep() { delete reference_; }
  private:
    MovementStep();

};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_STEP_H_