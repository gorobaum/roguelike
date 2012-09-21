
// Header File
#include "game/action/skill/movement_place.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameObject;

namespace game {
namespace action {
namespace skill {

Integer2D calculate_a(const GameObject* caster, const Integer2D& direction) {
    return Integer2D(0,0);
}

double spend_a(const GameObject* caster, const Integer2D& direction) {
    return 1.0;
}

void act_a(const GameObject* caster, const Integer2D& direction, double power) {
    return;
}

MovementPlace::MovementPlace() : super(calculate_a, spend_a, act_a) {}
MovementPlace::~MovementPlace() {}

} // namespace skill
} // namespace action
} // namespace game
