#ifndef ROGUELIKE_ACTION_SKILL_SKILL_H_
#define ROGUELIKE_ACTION_SKILL_SKILL_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
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

typedef std::list<base::GameThing> GameTargets;
typedef std::tr1::function<void (base::GameObject*, const GameTargets&, double)>
        GameAction;

class Skill {
  public:
    Skill() {}
    virtual ~Skill() {}

    virtual bool operator()(base::GameObject* caster, const GameTargets& targets) = 0;
    virtual bool operator()(base::GameObject* caster, const ugdk::math::Integer2D& target);
    virtual bool operator()(base::GameObject* caster, base::GameObject* target);
    virtual bool operator()(base::GameObject* caster);

    // Needed for GenericContainer
    static Skill* LoadFromFile(const std::string&) { return nullptr; }
};


} // namespace skill
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_SKILL_SKILL_H_ */