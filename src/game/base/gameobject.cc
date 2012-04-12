#include <ugdk/time/timeaccumulator.h>

#include <ugdk/graphic/node.h>

#include "game/base/gameobject.h"
#include "game/base/gametile.h"

#include "game/components/graphic.h"
#include "game/components/damageable.h"
#include "game/components/collision.h"
#include "game/components/controller.h"

using ugdk::Vector2D;

namespace game {

GameObject::GameObject(size_t scale_x, size_t scale_y, component::Graphic* graphic, component::Controller* controller, component::Collision* collision, component::Damageable* damageable)  
  : graphic_component_(graphic),
	controller_component_(controller),
	collision_component_(collision),
	damageable_component_(damageable),
	timed_life_(nullptr),
	dead_(false),
    dimensions_(Vector2D(scale_x, scale_y)) {}

GameObject::~GameObject() {
    delete graphic_component_;
	delete controller_component_;
	delete collision_component_;
    if(timed_life_) delete timed_life_;
    if(damageable_component_) delete damageable_component_;
}

void GameObject::Initialize() {
    this->controller_component_->set_owner(this);
    this->graphic_component_->set_owner(this);
    this->collision_component_->set_owner(this);
    this->damageable_component_->set_owner(this);
}

void GameObject::Update(double dt) {
    controller_component_->Update(dt, this);
    graphic_component_->Update(dt);
    if(damageable_component_) damageable_component_->Update(dt, this);
    if(timed_life_ && timed_life_->Expired()) Die();
}

void GameObject::UpdateNode() {
	this->graphic_component_->NodeLogic(occupying_tiles_);
	for(auto xt = occupying_tiles_.begin(); xt != occupying_tiles_.end(); ++xt) {
		(*xt)->node()->set_drawable(nullptr);
		(*xt)->set_update_node_flag(false);
	}
}
/*
GameTile* GameObject::game_tile() {
	if(tile_ == NULL) return NULL;
	return tile_;
}*/
/*
void GameObject::MoveTo(GameTile* tile) {
	if(tile_) tile_->RemoveObject(this);
	if(tile) {
		tile_ = tile;
		tile_->Collide(this);
		tile_->PushObject(this);
	}
}
*/
} // namespace game