// Header File
#include "game/base/gameobject.h"

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)

// Internal Dependencies
#include "game/component/controller.h"
#include "game/component/vision.h"
#include "game/component/damageable.h"
#include "game/component/shape.h"
#include "game/component/graphic.h"

// Using
using std::tr1::function;
using game::component::Controller;
using game::component::Vision;
using game::component::Damageable;
using game::component::Graphic;
using game::component::Shape;

namespace game {
namespace base {

GameObject::GameObject()
  : super(),
	controller_component_(nullptr),
    vision_component_(nullptr),
	damageable_component_(nullptr),
    shape_component_(nullptr),
    graphic_component_(nullptr) {}

GameObject::~GameObject() {
	if(controller_component_) delete controller_component_;
    if(vision_component_)     delete     vision_component_;
    if(damageable_component_) delete damageable_component_;
    if(shape_component_)      delete      shape_component_;
    if(graphic_component_)    delete    graphic_component_;
}

void GameObject::Initialize(
        Controller* controller_component,
        Vision*         vision_component,
        Damageable* damageable_component,
        Shape*           shape_component,
        Graphic*       graphic_component,
        const function<void (void)>& die ) {

    controller_component_ = controller_component;
    vision_component_     =     vision_component;
    damageable_component_ = damageable_component;
    shape_component_      =      shape_component;
    graphic_component_    =    graphic_component;
    die_ = die;
}

void GameObject::Update(double dt) {
    if(controller_component_) controller_component_->Update(dt);
    if(vision_component_)         vision_component_->Update(dt);

    if(graphic_component_)       graphic_component_->Update(dt);
}

} // namespace base
} // namespace game