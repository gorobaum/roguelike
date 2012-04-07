#include <ugdk/graphic/node.h>

#include "game/components/graphic_rectangular.h"

#include "game/gameobject.h"

namespace game {
namespace component {

void GraphicRectangular::Update(double dt, GameObject* owner) {
    super::Update(dt, owner);
}

void GraphicRectangular::NodeLogic(const std::list<GameTile*>& occupying_tiles_) {
    occupying_tiles_.front()->node()->AddChild(this->node());
}

} // namespace component
} // namespace game