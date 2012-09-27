// Header File
#include "game/base/gameobject.h"

// External Dependencies
#include <ugdk/portable/tr1.h>
#include FROM_TR1(functional)
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/action/skill/skillmanager.h"
#include "game/component/controller.h"
#include "game/component/vision.h"
#include "game/component/damageable.h"
#include "game/component/energy.h"
#include "game/component/shape.h"
#include "game/component/graphic.h"

// Defines
#define        USING_DEFINITION(compo,type) using game::component::type;
#define INITIALIZE_WITH_NULLPTR(compo,type) compo##_component_(nullptr),
#define       DESTRUCTOR_ACTION(compo,type) if(compo##_component_) delete compo##_component_;
#define     INI_ARG_DECLARATION(compo,type) type* compo##_component,
#define          INI_ASSIGNMENT(compo,type) compo##_component_ = compo##_component;
#define           UPDATE_ACTION(compo,type) if(compo##_component_) compo##_component_->Update(dt);

// Using
using std::string;
using std::tr1::function;
using ugdk::math::Integer2D;
using game::action::skill::GameTargets;
using game::action::skill::SkillManager;
FORALL_COMPONENTS(USING_DEFINITION) // note lack of ";"

namespace game {
namespace base {

GameObject::GameObject()
  : super(),
	FORALL_COMPONENTS(INITIALIZE_WITH_NULLPTR) // note lack of ","
    die_() {}

GameObject::~GameObject() {
	FORALL_COMPONENTS(DESTRUCTOR_ACTION) // note lack of ";"
}

void GameObject::Initialize( FORALL_COMPONENTS(INI_ARG_DECLARATION) // note lack of ","
                             const function<void (void)>& die ) {
    FORALL_COMPONENTS(INI_ASSIGNMENT) // note lack of ";"
    die_ = die;
}

void GameObject::Update(double dt) {
    FORALL_UPDATEABLE_COMPONENTS(UPDATE_ACTION) // note lack of ";"
}

bool GameObject::Cast(const string& skill, const GameTargets& targets) {
    return SkillManager::reference()->Cast(skill,this,targets);
}
bool GameObject::Cast(const string& skill, const Integer2D& target) {
    return SkillManager::reference()->Cast(skill,this,target);
}
bool GameObject::Cast(const string& skill, GameObject* target) {
    return SkillManager::reference()->Cast(skill,this,target);
}
bool GameObject::Cast(const string& skill) {
    return SkillManager::reference()->Cast(skill,this);
}

} // namespace base
} // namespace game