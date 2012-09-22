
// Header File
#include "game/action/skill/movement.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/gameaction.h"
#include "game/base/gamething.h"
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Using
using ugdk::math::Integer2D;
using game::action::GameTargets;
using game::base::GameObject;


// lambda FTW! Note how they have access to mov_ (these will be ran as Movement-methods).
#define TARGET_VALIDATOR(calculator)                                                    \
    [=](const GameObject* caster, const GameTargets& targets)->bool{                    \
        if( targets.front().is_obj() == true ) return false;                            \
        mov_ = calculator(caster, targets.front().tile());                              \
        if(is_relative)                                                                 \
            return mov_.x != 0 || mov_.y != 0;                                          \
        const Integer2D& tile = caster->shape_component()->occupying_tiles().front();   \
        return mov_.x != tile.x || mov_.y != tile.y;                                    \
    }

#define RESOURCE_SPENDER(spender)                                                       \
    [=](GameObject* caster, const GameTargets& targets)->double{                        \
         return spender(caster, mov_);                                                  \
    }

#define GAME_ACTION(action)                                                             \
    [=](GameObject* caster, const GameTargets& targets, double power)->void{            \
        return action(caster, mov_, power);                                             \
    }

namespace game {
namespace action {
namespace skill {


Movement::Movement( bool is_relative, const MovementCalculator& calculator,
                    const MovementSpender& spender, const MovementAction& action )
  : super( TARGET_VALIDATOR(calculator), RESOURCE_SPENDER(spender), GAME_ACTION(action) ) {}

} // namespace skill
} // namespace action
} // namespace game
