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
#include "game/base.h"

namespace game {
namespace component {

class ControllerAi : public Controller {
  typedef Controller super;

  public:
    ControllerAi::ControllerAi() : super() {}
    ~ControllerAi() {}

    void Update(double dt, game::base::GameObject* owner);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_AI_H_