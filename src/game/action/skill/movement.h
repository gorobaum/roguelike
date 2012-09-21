#ifndef ROGUELIKE_ACTION_SKILL_MOVEMENT_H_
#define ROGUELIKE_ACTION_SKILL_MOVEMENT_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
#include <list>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/action/gameaction.h"
#include "game/base/gamething.h"
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

typedef std::tr1::function<ugdk::math::Integer2D (const base::GameObject*, const ugdk::math::Integer2D&)>
        MovementCalculator;

typedef std::tr1::function<double (base::GameObject*, const ugdk::math::Integer2D&)>
        MovementSpender;

typedef std::tr1::function<void (base::GameObject*, const ugdk::math::Integer2D&, double)>
        MovementAction;

#define TARGET_VALIDATOR(calculator)                                                                \
    [=](const base::GameObject* caster, const std::list<base::GameThing*>& targets)->bool{          \
        if( targets.front()->is_obj() == true ) return false;                                       \
        mov_ = calculator(caster, targets.front()->tile());                                         \
        if(is_relative)                                                                             \
            return mov_.x != 0 || mov_.y != 0;                                                      \
        const ugdk::math::Integer2D& tile = caster->shape_component()->occupying_tiles().front();   \
        return mov_.x != tile.x || mov_.y != tile.y;                                                \
    }

#define RESOURCE_SPENDER(spender)                                                                   \
    [=](base::GameObject* caster, const std::list<base::GameThing*>& targets)->double{              \
         return spender(caster, mov_);                                                              \
    }

#define GAME_ACTION(action)                                                                         \
    [=](base::GameObject* caster, const std::list<base::GameThing*>& targets, double power)->void{  \
        return action(caster, mov_, power);                                                         \
    }


class Movement : public Skill {
  typedef Skill super;
  public:
    virtual ~Movement() {}

  protected:
    Movement( bool is_relative, const MovementCalculator& calculator,
              const MovementSpender& spender, const MovementAction& action )
      : super( TARGET_VALIDATOR(calculator), RESOURCE_SPENDER(spender), GAME_ACTION(action) ) {}

  private:
    ugdk::math::Integer2D mov_;

};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_H_