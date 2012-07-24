// Header File
#include "gametile.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/graphic/node.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using ugdk::Vector2D;
using game::base::GameObject;
using ugdk::base::ResourceManager;
using ugdk::graphic::Node;
using ugdk::graphic::TexturedRectangle;

namespace game {
namespace base {

const Vector2D GameTile::TILE_SIZE = Vector2D(23.0, 23.0);

GameTile::GameTile(int x, int y) : node_(new Node) {
	ground_ = new TexturedRectangle( ResourceManager::GetTextureFromFile("data/images/white.png") );
	node_->set_drawable(ground_);
    node_->modifier()->set_scale(Vector2D(0.382));
	x_ = x;
	y_ = y;
}

GameTile::~GameTile() { 
	node_->set_drawable(ground_);
	delete node_;
}

void GameTile::PushObject(GameObject* obj) {
	objects_here_.push_back(obj);
}

void GameTile::RemoveObject(GameObject* obj) {
	objects_here_.remove(obj);
}

} // namespace base
} // namespace game