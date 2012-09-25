#ifndef ROGUELIKE_ACTION_SKILL_MOVEMENT_H_
#define ROGUELIKE_ACTION_SKILL_MOVEMENT_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <ugdk/math/integer2D.h>

// Internal Dependencies
// (none)

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
    Movement( bool is_relative, const MovementCalculator& calculator,
              const MovementSpender& spender, const MovementAction& action );
    virtual ~Movement() {}

    bool operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    bool is_relative_;
    MovementCalculator calculator_;
    MovementSpender spender_;
    MovementAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_MOVEMENT_H_