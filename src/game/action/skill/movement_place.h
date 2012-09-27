#ifndef ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_
#define ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_

// Inheritance
#include "game/action/skill/movement.h"
#include "game/action/skill/skill.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

ugdk::math::Integer2D calculate_mov_place(const base::GameObject* caster, const ugdk::math::Integer2D& target);
void act_mov_place(base::GameObject* caster, const ugdk::math::Integer2D& target, double power);

class MovementPlace : public Movement {
  typedef Movement super;
  public:
    MovementPlace();
    ~MovementPlace() {}
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_PLACE_H_