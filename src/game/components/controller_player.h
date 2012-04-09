#ifndef BADGAME_COMPONENT_CONTROLLER_PLAYER_H_
#define BADGAME_COMPONENT_CONTROLLER_PLAYER_H_

#include <ugdk/time.h>
#include "game/components/controller.h"

namespace game {

class GameObject;

namespace component {

class ControllerPlayer : public Controller {
  typedef Controller super;
  public:
    ControllerPlayer() {}
    ~ControllerPlayer() {}

    void Update(double dt, GameObject* owner);

    GameTile* PlaceAt(game::GameTile* tile);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_PLAYER_H_