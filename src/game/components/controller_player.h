#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/components/controller.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/movement.h" // needed for where_to_

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ControllerPlayer : public Controller {
  typedef Controller super;
  public:
    ControllerPlayer(game::base::GameObject* owner);
    ~ControllerPlayer();

    void Update(double dt);

  private:
    game::action::Movement::Direction where_to_;
    bool special_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_