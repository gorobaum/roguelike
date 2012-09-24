#ifndef ROGUELIKE_ACTION_SKILL_SENSORY_H_
#define ROGUELIKE_ACTION_SKILL_SENSORY_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/action.h"
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

typedef std::tr1::function<double (base::GameObject*)>
        SenseSpender;

typedef std::tr1::function<void (base::GameObject*, double)>
        SenseAction;

class Sensory : public Skill {
  typedef Skill super;
  public:
    Sensory( const SenseSpender& spender,
             const  SenseAction&  action  );
    virtual ~Sensory() {}

    bool operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    SenseSpender spender_;
    SenseAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SENSORY_H_