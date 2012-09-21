#ifndef ROGUELIKE_COMPONENT_CONTROLLER_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_H_

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
    virtual ~Controller() {}

    virtual void Update(double dt) = 0;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_H_