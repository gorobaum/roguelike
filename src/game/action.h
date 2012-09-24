#ifndef ROGUELIKE_ACTION_H_
#define ROGUELIKE_ACTION_H_

#include <list>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

namespace game {
namespace action {

typedef std::list<base::GameThing> GameTargets;
typedef std::tr1::function<void (base::GameObject*, const GameTargets&, double)>
        GameAction;
class Skill;

} // namespace base
} // namespace game

#endif /* ROGUELIKE_ACTION_H_ */