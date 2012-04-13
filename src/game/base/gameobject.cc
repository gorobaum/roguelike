// Header File
#include "game/base/gameobject.h"

// External Dependencies
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/graphic/node.h>

// Internal Dependencies
#include "game/base/gametile.h"
#include "game/components/collision.h"
#include "game/components/controller.h"
#include "game/components/damageable.h"
#include "game/components/shape.h"
#include "game/components/graphic.h"

// Using
using ugdk::Vector2D;

namespace game {
namespace base {

GameObject::GameObject(component::Graphic* graphic, component::Controller* controller, component::Collision* collision, component::Shape* shape, component::Damageable* damageable)  
  : graphic_component_(graphic),
	controller_component_(controller),
	collision_component_(collision),
    shape_component_(shape),
	damageable_component_(damageable),
	dead_(false) {}

GameObject::~GameObject() {
    delete    graphic_component_;
	delete controller_component_;
	delete  collision_component_;
    delete      shape_component_;
    if(damageable_component_) delete damageable_component_;
}

void GameObject::Initialize() {
    controller_component_->set_owner(this);
    graphic_component_->set_owner(this);
    collision_component_->set_owner(this);
    shape_component_->set_owner(this);
    if(damageable_component_) damageable_component_->set_owner(this);
}

void GameObject::Update(double dt) {
    controller_component_->Update(dt);
    graphic_component_->Update(dt);
    if(damageable_component_) damageable_component_->Update(dt);
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

} // namespace base
} // namespace game