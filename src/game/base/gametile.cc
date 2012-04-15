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

namespace game {
namespace base {

const Vector2D GameTile::TILE_SIZE = Vector2D(16.0, 16.0);

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
	/*
	if (!objects_here_.empty())
		node_->RemoveChild( objects_here_.back()->graphic_component()->node() );
	*/
	objects_here_.push_back(obj);
	/*
	node_->AddChild(obj->graphic_component()->node());

	node_->set_drawable(NULL);
	*/
}

void GameTile::RemoveObject(GameObject* obj) {
	objects_here_.remove(obj);
	/*
	node_->RemoveChild(obj->graphic_component()->node());
	if (!objects_here_.empty())
		node_->AddChild( objects_here_.back()->graphic_component()->node() );
	else
		node_->set_drawable(ground_);
	*/
}

} // namespace base
} // namespace game