
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

namespace game {
namespace action {
namespace skill {

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
bool Skill::operator()(base::GameObject* caster) {
    GameTargets args;
    return operator()(caster, args);
}

} // namespace skill
} // namespace action
} // namespace game
