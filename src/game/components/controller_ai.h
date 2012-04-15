#ifndef BADGAME_COMPONENT_CONTROLLER_AI_H_
#define BADGAME_COMPONENT_CONTROLLER_AI_H_

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

class ControllerAi : public Controller {
  typedef Controller super;

  public:
    ControllerAi::ControllerAi(game::base::GameObject* owner) : super(owner) {}
    ~ControllerAi() {}

    void Update(double dt);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_AI_H_