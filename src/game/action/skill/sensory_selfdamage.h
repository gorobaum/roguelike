#ifndef ROGUELIKE_ACTION_SKILL_SENSORY_SELFDAMAGE_H_
#define ROGUELIKE_ACTION_SKILL_SENSORY_SELFDAMAGE_H_

// Inheritance
#include "game/action/skill/sensory.h"
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

class SensorySelfDamage : public Sensory {
  typedef Sensory super;
  public:
    static Skill& reference() { return reference_ == nullptr ? *(new SensorySelfDamage) : *reference_; }
    ~SensorySelfDamage() {}
  private:
    SensorySelfDamage();
    static SensorySelfDamage* reference_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SENSORY_SELFDAMAGE_H_