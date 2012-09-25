#ifndef ROGUELIKE_BASE_GAMEOBJECT_H_
#define ROGUELIKE_BASE_GAMEOBJECT_H_

// Inheritance
#include <ugdk/action/entity.h>

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <list>                 // template class
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace base {

class GameObject : public ugdk::action::Entity {
  typedef ugdk::action::Entity super;
  public:
    GameObject();
    ~GameObject();

    void Initialize(
        game::component::Controller* controller_component,
        game::component::Vision*         vision_component,
        game::component::Damageable* damageable_component,
        game::component::Energy*         energy_component,
        game::component::Shape*           shape_component,
        game::component::Graphic*       graphic_component,

        const std::tr1::function<void (void)>& die = std::tr1::function<void (void)>()
    );

    void Update(double dt);
    
          component::Controller* controller_component()       { return controller_component_; }
    const component::Controller* controller_component() const { return controller_component_; }
          component::Vision*         vision_component()       { return     vision_component_; }
    const component::Vision*         vision_component() const { return     vision_component_; }

          component::Damageable* damageable_component()       { return damageable_component_; }
    const component::Damageable* damageable_component() const { return damageable_component_; }
          component::Energy*         energy_component()       { return     energy_component_; }
    const component::Energy*         energy_component() const { return     energy_component_; }
          component::Shape*           shape_component()       { return      shape_component_; }
    const component::Shape*           shape_component() const { return      shape_component_; }

          component::Graphic*       graphic_component()       { return    graphic_component_; }
    const component::Graphic*       graphic_component() const { return    graphic_component_; }

    void Die() { die_(); to_be_removed_ = true; }
    bool dead() const { return to_be_removed_; }

  private:
    component::Controller* controller_component_;
    component::Vision*         vision_component_;

    component::Damageable* damageable_component_;
    component::Energy*         energy_component_;
    component::Shape*           shape_component_;

    component::Graphic*       graphic_component_;

    std::tr1::function<void (void)> die_;
};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_GAMEOBJECT_H_