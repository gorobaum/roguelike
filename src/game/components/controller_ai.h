#ifndef BADGAME_COMPONENT_CONTROLLER_AI_H_
#define BADGAME_COMPONENT_CONTROLLER_AI_H_

#include <ugdk/graphic.h>
#include <ugdk/time.h>
#include "game/components/controller.h"

namespace game {
namespace component {

class ControllerAi : public Controller {
  typedef Controller super;

  public:
    ControllerAi::ControllerAi() : timer_(new ugdk::time::TimeAccumulator(0)) {}
    ~ControllerAi() { delete timer_; }

    void Update(double dt, GameObject* owner);

    GameTile* PlaceAt(game::GameTile* tile) { return tile; } //TODO: Fazer essa fun��o fazer algo.

  private:
    static const double VELOCITY, MIN_WAIT, MAX_WAIT;
    ugdk::time::TimeAccumulator* timer_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_AI_H_