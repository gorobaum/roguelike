#ifndef ROGUELIKE_ACTION_SKILL_SELF_LIGHT_H_
#define ROGUELIKE_ACTION_SKILL_SELF_LIGHT_H_

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

class SelfLight : public Self {
  typedef Self super;
  public:
    static Skill& reference() { return reference_ == nullptr ? *(new SelfLight) : *reference_; }
    ~SelfLight() {}
  private:
    SelfLight();
    static SelfLight* reference_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SELF_LIGHT_H_