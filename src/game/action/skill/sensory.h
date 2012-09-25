#ifndef ROGUELIKE_ACTION_SKILL_SELF_H_
#define ROGUELIKE_ACTION_SKILL_SELF_H_

// Inheritance
#include "game/action/skill/skill.h"

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace action {
namespace skill {

typedef std::tr1::function<double (base::GameObject*)>
        SenseSpender;

typedef std::tr1::function<void (base::GameObject*, double)>
        SenseAction;

class Self : public Skill {
  typedef Skill super;
  public:
    Self( const SenseSpender& spender,
             const  SenseAction&  action  );
    virtual ~Self() {}

    bool operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    SenseSpender spender_;
    SenseAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SELF_H_