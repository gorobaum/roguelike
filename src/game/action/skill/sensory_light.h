#ifndef ROGUELIKE_ACTION_SKILL_SENSORY_LIGHT_H_
#define ROGUELIKE_ACTION_SKILL_SENSORY_LIGHT_H_

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

class SensoryLight : public Sensory {
  typedef Sensory super;
  public:
    static Skill& reference() { return reference_ == nullptr ? *(new SensoryLight) : *reference_; }
    ~SensoryLight() {}
  private:
    SensoryLight();
    static SensoryLight* reference_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SENSORY_LIGHT_H_