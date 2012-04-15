// Header File
#include "game/components/graphic_rectangular.h"

// External Dependencies
#include <ugdk/base/engine.h>           // needed in the TEXT_MANAGER() macro
#include <ugdk/graphic/drawable/text.h> // needed for GetText(-)
#include <ugdk/graphic/node.h>          // needed for set_drawable(-)
#include <ugdk/graphic/textmanager.h>   // needed for the TEXT_MANAGER() macro

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/shape_rectangular.h"

// Using
using std::list;
using std::wstring;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace component {

GraphicRectangular::GraphicRectangular(GameObject* owner, wstring visual_representation) : super(owner) {
    node()->set_drawable(TEXT_MANAGER()->GetText(visual_representation));
}
GraphicRectangular::~GraphicRectangular() {}

void GraphicRectangular::Update(double dt) {
    /* animation stuff goes here */
}

void GraphicRectangular::NodeLogic(const list<GameTile*>& occupying_tiles) {
    node()->modifier()->set_scale(static_cast<ShapeRectangular*>(owner_->shape_component())->dimensions());
    occupying_tiles.front()->node()->AddChild(this->node());
}

} // namespace component
} // namespace game