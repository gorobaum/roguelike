#include <ugdk/graphic/node.h>

#include "game/components/graphic_rectangular.h"

#include "game/base/gameobject.h"

namespace game {
namespace component {

void GraphicRectangular::Update(double dt) {
}

void GraphicRectangular::NodeLogic(const std::list<GameTile*>& occupying_tiles_) {
    occupying_tiles_.front()->node()->AddChild(this->node());
    node()->modifier()->set_scale(owner_->dimensions());
}

} // namespace component
} // namespace game