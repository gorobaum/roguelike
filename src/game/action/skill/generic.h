#ifndef ROGUELIKE_ACTION_SKILL_GENERIC_H_
#define ROGUELIKE_ACTION_SKILL_GENERIC_H_

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

typedef std::tr1::function<bool (const base::GameObject*, const GameTargets&)>
        GenericValidator;

typedef std::tr1::function<double (base::GameObject*, const GameTargets&)>
        GenericSpender;

class Generic : public Skill {
  typedef Skill super;
  public:
    Generic(const GenericValidator& validator, const GenericSpender& spender, const GameAction& action);
    virtual ~Generic() {}

    bool operator()(base::GameObject* caster, const GameTargets& targets);

  private:
    GenericValidator validator_;
    GenericSpender spender_;
    GameAction action_;
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_GENERIC_H_