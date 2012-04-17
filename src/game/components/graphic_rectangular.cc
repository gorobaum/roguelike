#include <math.h>

// Header File
#include "game/components/graphic_rectangular.h"

// External Dependencies
#include <ugdk/graphic/node.h>

#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/shape_rectangular.h"

// Using
using std::list;
using std::string;
using game::base::GameObject;
using game::base::GameTile;

using ugdk::Vector2D;

namespace game {
namespace component {

GraphicRectangular::GraphicRectangular(GameObject* owner, string visual_representation, double zindex)
  : super(owner, visual_representation, zindex) {}
GraphicRectangular::~GraphicRectangular() {}

void GraphicRectangular::Update(double dt) {
}

void GraphicRectangular::NodeLogic(const list<GameTile*>& occupying_tiles) {
    node()->modifier()->set_scale( (static_cast<ShapeRectangular*>(owner_->shape_component())->dimensions())*0.382 );
    occupying_tiles.front()->node()->AddChild(this->node());
}

} // namespace component
} // namespace game