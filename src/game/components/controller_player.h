#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/components/controller.h"

// External Dependencies
//#include <ugdk/time.h>    // needed for 

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

    void Update(double dt, game::base::GameObject* owner);

    game::base::GameTile* PlaceAt(game::base::GameTile* tile);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_