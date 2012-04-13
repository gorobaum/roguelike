#ifndef BADGAME_COMPONENT_CONTROLLER_H_
#define BADGAME_COMPONENT_CONTROLLER_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include "game/base.h"

namespace game {
namespace component {

class Controller {
  public:
    Controller() : owner_(nullptr) {}
    ~Controller() {}

    void set_owner(game::base::GameObject* owner) { owner_ = owner; } //TODO: Mudar para ser no construtor

    virtual void Update(double dt) = 0;

  protected:
    game::base::GameObject* owner_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_CONTROLLER_H_