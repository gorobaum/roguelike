// Header File
#include "game/base/gameobject.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/components/collision.h"
#include "game/components/controller.h"
#include "game/components/damageable.h"
#include "game/components/shape.h"
#include "game/components/graphic.h"

// Using
using game::component::Collision;
using game::component::Controller;
using game::component::Damageable;
using game::component::Graphic;
using game::component::Shape;

namespace game {
namespace base {

GameObject::GameObject()
  : super(),
	controller_component_(nullptr),
	collision_component_(nullptr),
	damageable_component_(nullptr),
    shape_component_(nullptr),
    graphic_component_(nullptr),
	dead_(false) {}

GameObject::~GameObject() {
	if(controller_component_) delete controller_component_;
	if(collision_component_)  delete  collision_component_;
    if(damageable_component_) delete damageable_component_;
    if(shape_component_)      delete      shape_component_;
    if(graphic_component_)    delete    graphic_component_;
}

void GameObject::Initialize(
        Controller* controller_component,
        Collision*   collision_component,
        Damageable* damageable_component,
        Shape*           shape_component,
        Graphic*       graphic_component ) {

    controller_component_ = controller_component;
    collision_component_  =  collision_component;
    damageable_component_ = damageable_component;
    shape_component_      =      shape_component;
    graphic_component_    =    graphic_component;
}

void GameObject::Update(double dt) {
    if(controller_component_) controller_component_->Update(dt);
    if(damageable_component_) damageable_component_->Update(dt);
    if(graphic_component_)       graphic_component_->Update(dt);
}

} // namespace base
} // namespace game