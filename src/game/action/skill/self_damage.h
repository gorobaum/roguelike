#ifndef ROGUELIKE_ACTION_SKILL_SELF_DAMAGE_H_
#define ROGUELIKE_ACTION_SKILL_SELF_DAMAGE_H_

// Inheritance
#include "game/action/skill/self.h"
#include "game/action/skill/skill.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {
namespace skill {

class SelfDamage : public Self {
  typedef Self super;
  public:
    SelfDamage();
    ~SelfDamage() {}
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SELF_DAMAGE_H_