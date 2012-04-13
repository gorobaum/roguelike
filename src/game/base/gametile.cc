// Header File
#include "gametile.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/components/collision.h"
#include "game/components/graphic.h"

// Using
using ugdk::Vector2D;
using ugdk::graphic::Node;
using ugdk::graphic::SolidRectangle;

namespace game {
namespace base {

const Vector2D GameTile::TILE_SIZE = Vector2D(16.0, 16.0);

GameTile::GameTile(size_t x, size_t y) : node_(new Node) {
	/* double z = 0.4;
	SolidRectangle* rect = new SolidRectangle(TILE_SIZE - ugdk::Vector2D(1));
	rect->set_color(ugdk::Color(z, z, z)); */
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
/*
void GameTile::Collide(GameObject* obj) {
	for (std::list<GameObject*>::iterator it = objects_.begin(); it != objects_.end(); ++it)
		obj->collision_component()->Handle(*it);
}*/

} // namespace base
} // namespace game