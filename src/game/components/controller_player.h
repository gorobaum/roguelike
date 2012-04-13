#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

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

class ControllerPlayer : public Controller {
  typedef Controller super;
  public:
    ControllerPlayer() {}
    ~ControllerPlayer() {}

    void Update(double dt);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_