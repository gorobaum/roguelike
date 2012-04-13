#ifndef BADGAME_BASE_GAMEOBJECT_H_
#define BADGAME_BASE_GAMEOBJECT_H_

// Inheritance
#include <ugdk/action/entity.h>

// External Dependencies
#include <list>                 // template class
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace base {

class GameObject : public ugdk::Entity {
  typedef ugdk::Entity super;
  public:
    GameObject(component::Graphic*, component::Controller* controller, component::Collision* collision, component::Shape* shape, component::Damageable* = nullptr);
    ~GameObject();

    void Initialize();

    void Update(double dt);

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Controller* controller_component() { return controller_component_; }
    component::Damageable* damageable_component() { return damageable_component_; }
    component::Shape*           shape_component() { return      shape_component_; }
	component::Collision*   collision_component() { return  collision_component_; }

    void Die() { dead_ = true; }
    bool dead() const { return dead_; }

  private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
    component::Collision*   collision_component_;
    component::Shape*           shape_component_;
    component::Damageable* damageable_component_;
    
    bool dead_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMEOBJECT_H_