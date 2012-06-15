#ifndef BADGAME_COMPONENT_VISION_H_
#define BADGAME_COMPONENT_VISION_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
#include <list> // eye()

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/components/shape.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Vision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Vision(game::base::GameObject* owner) : super(owner) {}
    ~Vision() {}

    base::GameTile* eye() const { return owner_->shape_component()->occupying_tiles().front(); }
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_VISION_H_