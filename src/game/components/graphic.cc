// Header File
#include "game/components/graphic.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using ugdk::graphic::Node;
using game::base::GameObject;

namespace game {
namespace component {

Graphic::Graphic(GameObject* owner, std::wstring visual_representation, double zindex)
  : super(owner), node_(new Node()) {
    node_->set_drawable(TEXT_MANAGER()->GetText(visual_representation));
    node_->set_zindex(zindex);
}
Graphic::~Graphic() { delete node_; }

} // namespace component
} // namespace game