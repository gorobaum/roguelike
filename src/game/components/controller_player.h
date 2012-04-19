#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/components/controller.h"

// External Dependencies
#include <ugdk/time/timeaccumulator.h> // needed for time_held_

// Internal Dependencies
#include "game/action/movement.h" // needed for where_to_

// Forward Declarations
#include <ugdk/time.h>
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
    ugdk::time::TimeAccumulator time_held_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_