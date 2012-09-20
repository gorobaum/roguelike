#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/component/controller.h"

// External Dependencies
#include <ugdk/math/integer2D.h> // where_to_
#include <ugdk/time/timeaccumulator.h> // time_held_

// Internal Dependencies
// (none)

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
    ugdk::math::Integer2D where_to_;
    ugdk::time::TimeAccumulator time_held_;
    ugdk::time::TimeAccumulator hold_tick_;

    bool held_movement_adjusted_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_