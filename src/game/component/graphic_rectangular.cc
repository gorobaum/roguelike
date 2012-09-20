
// Header File
#include "game/component/graphic_rectangular.h"

// External Dependencies
#include <cmath>
#include <ugdk/graphic/node.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/shape_rectangular.h"

// Using
using std::list;
using std::string;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using ugdk::Vector2D;
using ugdk::math::Integer2D;

namespace game {
namespace component {

GraphicRectangular::GraphicRectangular(GameObject* owner, string visual_representation, double zindex)
  : super(owner, visual_representation, zindex) {}
GraphicRectangular::~GraphicRectangular() {}

void GraphicRectangular::Update(double) {}

void GraphicRectangular::NodeLogic(const list<Integer2D>& occupying_tiles) {
	const GameController* gamecontroller = GameController::reference();

    node()->modifier()->set_scale( Vector2D(static_cast<ShapeRectangular*>(owner_->shape_component())->dimensions())*0.382 );
	node()->modifier()->set_offset( gamecontroller->Tile(occupying_tiles.front())->node()->modifier()->offset() );
}

} // namespace component
} // namespace game