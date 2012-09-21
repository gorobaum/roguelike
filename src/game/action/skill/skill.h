#ifndef ROGUELIKE_ACTION_SKILL_SKILL_H_
#define ROGUELIKE_ACTION_SKILL_SKILL_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
#include "game/action/gameaction.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

class Skill {
  public:
    virtual ~Skill() { if(reference_) delete reference_; }

    bool operator()(base::GameObject* caster, const GameTargets& targets) {
        if( target_validator_(caster,targets) ) {
            double power = resource_spender_(caster,targets);
            if( power != 0.0 ) {
                action_(caster,targets,power);
                return true;
            }
        }
        return false;
    }

  protected:
    Skill( const TargetValidator& target_validator,
           const ResourceSpender& resource_spender,
           const GameAction& action )
      : target_validator_(target_validator),
        resource_spender_(resource_spender),
        action_(action) {
        reference_ = this;
    }

    static Skill* reference_;

  private:
    TargetValidator target_validator_;
    ResourceSpender resource_spender_;
    GameAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILL_H_ */