#ifndef ROGUELIKE_ACTION_SKILL_SKILL_H_
#define ROGUELIKE_ACTION_SKILL_SKILL_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"
#include "game/action.h"

namespace game {
namespace action {
namespace skill {

class Skill {
  public:
    Skill() {}
    virtual ~Skill() {}

    virtual bool operator()(base::GameObject* caster, const GameTargets& targets) = 0;
    virtual bool operator()(base::GameObject* caster, const ugdk::math::Integer2D& target);
    virtual bool operator()(base::GameObject* caster, base::GameObject* target);
    virtual bool operator()(base::GameObject* caster);
};

} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILL_H_ */