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

class ControllerIdle : public Controller {
  typedef Controller super;
  public:
    ControllerIdle(game::base::GameObject* owner) : super(owner) {}
    ~ControllerIdle() {}

    void Update(double dt);
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_CONTROLLER_IDLE_H_