
// Header File
#include "game/action/skill/movement_step.h"

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

Integer2D calculate(const GameObject* caster, const Integer2D& direction) {
    return Integer2D(0,0);
}

double spend(const GameObject* caster, const Integer2D& direction) {
    return 1.0;
}

void act(const GameObject* caster, const Integer2D& direction, double power) {
    return;
}

MovementStep::MovementStep() : super(calculate, spend, act) {}
MovementStep::~MovementStep() {}

} // namespace skill
} // namespace action
} // namespace game
