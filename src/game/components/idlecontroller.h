#ifndef TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_

#include <ugdk/graphic.h>
#include "game/components/controller.h"

namespace game {

class GameObject;

namespace component {

class IdleController : public Controller {
  typedef Controller super;
  public:
    IdleController() {}
    ~IdleController() {}

    void Update(double dt, GameObject* owner) {}
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_