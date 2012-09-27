#ifndef ROGUELIKE_BASE_GAMEOBJECT_H_
#define ROGUELIKE_BASE_GAMEOBJECT_H_

// Inheritance
#include <ugdk/action/entity.h>

// External Dependencies
#include <string>
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <list>                 // template class
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
#include "game/action/skill/skill.h"

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

// Defines
#define FORALL_UPDATEABLE_COMPONENTS(action)    \
    action( controller, Controller)             \
    action(    graphic,    Graphic)

#define FORALL_COMPONENTS(action)           \
    action( controller, Controller)         \
    action(     vision,     Vision)         \
    action( damageable, Damageable)         \
    action(     energy,     Energy)         \
    action(      shape,      Shape)         \
    action(    graphic,    Graphic)


#define FULL_TYPE(type) component::type*

#define INI_FULLTYPE_ARG_DECLARATION(compo,type) FULL_TYPE(type) compo##_component,

#define GETTER_DECLARATION(compo,type)                                              \
          FULL_TYPE(type) compo##_component()       { return compo##_component_; }  \
    const FULL_TYPE(type) compo##_component() const { return compo##_component_; }

#define SETTER_DECLARATION(compo,type)                                                                          \
    void set_##compo##_component(FULL_TYPE(type) compo##_component) { compo##_component_ = compo##_component; }

#define ATTRIBUTES_DECLARATION(compo,type) FULL_TYPE(type) compo##_component_;


namespace game {
namespace base {

class GameObject : public ugdk::action::Entity {
  typedef ugdk::action::Entity super;
  public:
    GameObject();
    ~GameObject();

    void Initialize(
        FORALL_COMPONENTS(INI_FULLTYPE_ARG_DECLARATION) // note lack of ","
        const std::tr1::function<void (void)>& die = std::tr1::function<void (void)>()
    );

    void Update(double dt);
    
    FORALL_COMPONENTS(GETTER_DECLARATION) // ends in "}"
    FORALL_COMPONENTS(SETTER_DECLARATION) // ends in "}"

    bool Cast(const std::string& skill, const action::skill::GameTargets& targets);
    bool Cast(const std::string& skill, const ugdk::math::Integer2D& target);
    bool Cast(const std::string& skill, base::GameObject* target);
    bool Cast(const std::string& skill);

    void Die() { die_(); to_be_removed_ = true; }
    bool dead() const { return to_be_removed_; }

  private:
    FORALL_COMPONENTS(ATTRIBUTES_DECLARATION) // note lack of ";"
    std::tr1::function<void (void)> die_;
};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_GAMEOBJECT_H_