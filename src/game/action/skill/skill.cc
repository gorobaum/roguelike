
// Header File
#include "game/action/skill/skill.h"

// External Dependencies
#include <list>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gamething.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameObject;
using game::base::GameThing;

namespace game {
namespace action {
namespace skill {

Skill* Skill::reference_ = nullptr;

bool Skill::operator()(GameObject* caster, const GameTargets& targets) {
    if( target_validator_(caster,targets) ) {
        double power = resource_spender_(caster,targets);
        if( power != 0.0 ) {
            action_(caster,targets,power);
            return true;
        }
    }
    return false;
}
bool Skill::operator()(GameObject* caster, const Integer2D& target) {
    GameTargets args;
    args.push_back(target);
    return operator()(caster, args);
}
bool Skill::operator()(GameObject* caster, GameObject* target) {
    GameTargets args;
    args.push_back(target);
    return operator()(caster, args);
}

} // namespace skill
} // namespace action
} // namespace game
