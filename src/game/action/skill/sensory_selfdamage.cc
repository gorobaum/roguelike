
// Header File
#include "game/action/skill/sensory_selfdamage.h"

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

static double spend_selfdamage(GameObject* caster) {
    return 1.0;
}

static void act_selfdamage(GameObject* caster, double power) {
    caster->damageable_component()->TakeDamage(9001.1337042);
}

SensorySelfDamage* SensorySelfDamage::reference_ = nullptr;

SensorySelfDamage::SensorySelfDamage()
  : super(spend_selfdamage, act_selfdamage) {}

} // namespace skill
} // namespace action
} // namespace game
