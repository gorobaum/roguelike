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

class Movement : public Skill {
  typedef Skill super;
  public:
    Movement( const MovementCalculator& calculator,
              const MovementSpender& spender, 
              const MovementAction& action )
      : super( [&, this](const base::GameObject* caster, const std::list<base::GameThing*>& targets)->bool{
                   if( targets.front()->is_obj() == true ) return false;
                   mov_ = calculator(caster, targets.front()->tile());
                   return mov_.x != 0 || mov_.y != 0;
               },
               [&, this](base::GameObject* caster, const std::list<base::GameThing*>& targets)->double{
                   return spender(caster, mov_);
               },
               [&, this](base::GameObject* caster, const std::list<base::GameThing*>& targets, double power)->void{
                   return action(caster, mov_, power);
               }
        ) {
    }
    ~Movement() {}

  private:
    ugdk::math::Integer2D mov_;

};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_H_