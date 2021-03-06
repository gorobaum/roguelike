// Header File
#include "game/component/graphic.h"

// External Dependencies
#include <ugdk/graphic/node.h>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using std::string;
using ugdk::graphic::Node;
using game::base::GameObject;
using ugdk::Vector2D;
using ugdk::graphic::TexturedRectangle;
using ugdk::base::ResourceManager;

namespace game {
namespace component {

Graphic::Graphic(GameObject* owner, const string& visual_representation, double zindex)
  : super(owner), node_(new Node()) {
    node_->set_drawable(new TexturedRectangle( ResourceManager::GetTextureFromFile("images/"+visual_representation+".png") ) );
    node_->set_zindex(zindex);
}
Graphic::~Graphic() { delete node_; }

} // namespace component
} // namespace game