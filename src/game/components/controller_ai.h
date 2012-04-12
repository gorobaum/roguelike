#ifndef BADGAME_COMPONENT_CONTROLLER_AI_H_
#define BADGAME_COMPONENT_CONTROLLER_AI_H_

// Inheritance
#include "game/components/controller.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include <ugdk/time.h>
#include "game/base.h"

namespace game {
namespace component {

class ControllerAi : public Controller {
  typedef Controller super;

  public:
    ControllerAi::ControllerAi() : timer_(new ugdk::time::TimeAccumulator(0)) {}
    ~ControllerAi() { delete timer_; }

    void Update(double dt, game::base::GameObject* owner);

    game::base::GameTile* PlaceAt(game::base::GameTile* tile) { return tile; } //TODO: Fazer essa função fazer algo.

  private:
    static const double VELOCITY, MIN_WAIT, MAX_WAIT;
    ugdk::time::TimeAccumulator* timer_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_AI_H_