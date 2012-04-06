#ifndef BADGAME_COMPONENT_PLAYERCONTROLLER_H_
#define BADGAME_COMPONENT_PLAYERCONTROLLER_H_

#include <ugdk/time.h>
#include "game/components/controller.h"
#include "game.h"

namespace game {
namespace component {

class PlayerController : public Controller {
  typedef Controller super;
  public:
    PlayerController();
    ~PlayerController();

    void Update(double dt, GameObject* owner);

  private:

};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_PLAYERCONTROLLER_H_