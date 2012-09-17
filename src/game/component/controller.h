#ifndef BADGAME_COMPONENT_CONTROLLER_H_
#define BADGAME_COMPONENT_CONTROLLER_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Controller : public ComponentBase {
  typedef ComponentBase super;
  public:
    Controller(game::base::GameObject* owner) : super(owner) {}
    ~Controller() {}

    virtual void Update(double dt) = 0;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_H_