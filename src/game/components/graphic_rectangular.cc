// Header File
#include "game/components/graphic_rectangular.h"

// External Dependencies

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/shape_rectangular.h"

// Using
using std::list;
using game::base::GameTile;

namespace game {
namespace component {

void GraphicRectangular::Update(double dt) {
}

void GraphicRectangular::NodeLogic(const list<GameTile*>& occupying_tiles) {
    occupying_tiles.front()->node()->AddChild(this->node());
    node()->modifier()->set_scale(static_cast<ShapeRectangular*>(owner_->shape_component())->dimensions());
}

} // namespace component
} // namespace game