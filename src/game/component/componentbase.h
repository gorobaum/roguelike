#ifndef BADGAME_COMPONENT_COMPONENTBASE_H_
#define BADGAME_COMPONENT_COMPONENTBASE_H_

// Inheritance
// (none)

// External Dependencies
//(none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ComponentBase {
  public:
    ComponentBase(game::base::GameObject* owner) : owner_(owner) {}
    ~ComponentBase() {}

  protected:
    game::base::GameObject* owner_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_COMPONENTBASE_H_