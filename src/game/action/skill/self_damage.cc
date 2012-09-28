
// Header File
#include "game/action/skill/self_damage.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/damageable.h"

// Using
using game::base::GameObject;
using game::component::Damageable;

namespace game {
namespace action {
namespace skill {

static double spend_damage(GameObject* caster) {
    return 1.0;
}

static void act_damage(GameObject* caster, double power) {
    caster->damageable_component()->TakeDamage(9001.1337042);
}

SelfDamage::SelfDamage()
  : super(spend_damage, act_damage) {}

} // namespace skill
} // namespace action
} // namespace game
