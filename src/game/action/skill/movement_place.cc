
// Header File
#include "game/action/skill/movement_place.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameObject;
using game::component::Shape;

namespace game {
namespace action {
namespace skill {

Integer2D calculate_mov_place(const GameObject* caster, const Integer2D& target) {
    const Shape* shape = caster->shape_component();

    if(caster->shape_component()->TryPlace(target))
        return target;
    return shape->occupying_tiles().front();
}

static double spend_mov_place(GameObject* caster, const Integer2D& target) {
    return 1.0;
}

void act_mov_place(GameObject* caster, const Integer2D& target, double power) {
    caster->shape_component()->PlaceAt(target);
}

MovementPlace* MovementPlace::reference_ = nullptr;

MovementPlace::MovementPlace()
  : super(false, calculate_mov_place, spend_mov_place, act_mov_place) {}

} // namespace skill
} // namespace action
} // namespace game
