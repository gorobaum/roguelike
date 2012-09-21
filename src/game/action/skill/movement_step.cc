
// Header File
#include "game/action/skill/movement_step.h"

// External Dependencies
#include <list>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/action/skill/movement_place.h"
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameObject;

namespace game {
namespace action {
namespace skill {

static Integer2D calculate_mov_step(const GameObject* caster, const Integer2D& direction) {
    Integer2D position = caster->shape_component()->occupying_tiles().front();
    Integer2D to_where = position+direction;
    Integer2D trystep = calculate_mov_place(caster,to_where);

    if( direction.x == 0 || direction.y == 0 )
        return trystep - position;
    
    Integer2D trycomponent = calculate_mov_place(caster,Integer2D(to_where.x,position.y));
    if(trystep.x == to_where.x && trystep.y == to_where.y ) {
        if(trycomponent.x == to_where.x)
            return trystep - position;
        trycomponent = calculate_mov_place(caster,Integer2D(position.x,to_where.y));
        if(trycomponent.y == to_where.y)
            return trystep - position;
    }
    if(trycomponent.x == to_where.x) {
        trystep = calculate_mov_place(caster,Integer2D(position.x,to_where.y));
        if(trystep.y != to_where.y)
            return trycomponent - position;
    } else {
        trystep = calculate_mov_place(caster,Integer2D(position.x,to_where.y));
        if(trystep.y == to_where.y)
            return trystep - position;
    }
    return Integer2D(0,0);
}

static double spend_mov_step(GameObject* caster, const Integer2D& direction) {
    return 1.0;
}

static void act_mov_step(GameObject* caster, const Integer2D& direction, double power) {
    Integer2D position = caster->shape_component()->occupying_tiles().front();
    return act_mov_place(caster,position+direction,power);
}

MovementStep::MovementStep()
  : super(true, calculate_mov_step, spend_mov_step, act_mov_step) {}

} // namespace skill
} // namespace action
} // namespace game
