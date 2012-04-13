#ifndef TOPDOWN_GAME_COMPONENT_CONTROLLER_IDLE_H_
#define TOPDOWN_GAME_COMPONENT_CONTROLLER_IDLE_H_

// Inheritance
#include "game/components/controller.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class IdleController : public Controller {
  typedef Controller super;
  public:
    IdleController() {}
    ~IdleController() {}

    void Update(double dt, game::base::GameObject* owner) {}
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_CONTROLLER_IDLE_H_