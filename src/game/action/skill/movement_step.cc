
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
    // we'll need at least this info:
    Integer2D position = caster->shape_component()->occupying_tiles().front();
    Integer2D to_where = position+direction;
    Integer2D trystep = calculate_mov_place(caster,to_where);
    
    // non-diagonal steps are easy:
    if( direction.x == 0 || direction.y == 0 )
        return trystep - position;

    // diagonal movement fully succeeds only if you could place yourself at destination,
    // and it requires at least one free non-diagonal path to it.
    // (the path needs to exist for the movement to be valid,
    //  however, the object doesn't actually step through it)

    // first try the horizontal path.
    Integer2D trycomponent = calculate_mov_place(caster,Integer2D(to_where.x,position.y));
    if(trycomponent.x == to_where.x) {
        // the horizontal path is free? Then if trystep is correct, we should move there.
        if(trystep.x == to_where.x) // (this implies trystep.y == to_where.y) 
            return trystep - position;

        // otherwise, if the vertical path is not free, we should move horizontally.
        trystep = calculate_mov_place(caster,Integer2D(position.x,to_where.y));
        if(trystep.y != to_where.y)
            return trycomponent - position;

        // if the vertical path is also free, we can't decide for the player which side to move to.
        return Integer2D(0,0);
    }

    // second, try the vertical path.
    trycomponent = calculate_mov_place(caster,Integer2D(position.x,to_where.y));
    if(trycomponent.y == to_where.y) {
        // this time around there's only two possibilities: either the corner is free,
        // and we should move there, or it's not free, and we should move vertically.
        if(trystep.x == to_where.x)
            return trystep - position;
        return trycomponent - position;
    }
    
    // finally, if no paths are free, then it doesn't matter if the corner is free, we can't move.
    return Integer2D(0,0);
}

static double spend_mov_step(GameObject* caster, const Integer2D& direction) {
    return 1.0;
}

static void act_mov_step(GameObject* caster, const Integer2D& direction, double power) {
    Integer2D position = caster->shape_component()->occupying_tiles().front();
    return act_mov_place(caster,position+direction,power);
}

MovementStep* MovementStep::reference_ = nullptr;

MovementStep::MovementStep()
  : super(true, calculate_mov_step, spend_mov_step, act_mov_step) {}

} // namespace skill
} // namespace action
} // namespace game
