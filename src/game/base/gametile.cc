// Header File
#include "gametile.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using ugdk::Vector2D;
using ugdk::graphic::Node;
using game::base::GameObject;

namespace game {
namespace base {

const Vector2D GameTile::TILE_SIZE = Vector2D(23.0, 23.0);

GameTile::GameTile(size_t x, size_t y) : node_(new Node) {
	ground_ = TEXT_MANAGER()->GetText(L".");
	node_->set_drawable(ground_);
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