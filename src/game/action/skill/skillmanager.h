#ifndef ROGUELIKE_ACTION_SKILL_SKILLMANAGER_H_
#define ROGUELIKE_ACTION_SKILL_SKILLMANAGER_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/base/genericcontainer.h>

// Internal Dependencies
#include "game/action/skill/skill.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

class SkillManager : public ugdk::base::GenericContainer<Skill*> {
  typedef ugdk::base::GenericContainer<Skill*> super;
  // singleton
  static SkillManager* reference_;
  SkillManager();

  public:
    static SkillManager* reference() {
        return reference_ == nullptr
          ? (reference_ = new SkillManager())
          : reference_ ;
    }
    ~SkillManager();


    bool Cast(const std::string& skill, base::GameObject* caster, const GameTargets& targets) {
        return (*Find(skill))(caster, targets);
    }
    bool Cast(const std::string& skill, base::GameObject* caster, const ugdk::math::Integer2D& target) {
        return (*Find(skill))(caster, target);
    }
    bool Cast(const std::string& skill, base::GameObject* caster, base::GameObject* target) {
        return (*Find(skill))(caster, target);
    }
    bool Cast(const std::string& skill, base::GameObject* caster) {
        return (*Find(skill))(caster);
    }
};

} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILLMANAGER_H_ */