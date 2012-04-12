// Header File
#include "game/builders/objectbuilder.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time/timeaccumulator.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/collision.h"
#include "game/components/controller_ai.h"
#include "game/components/controller_player.h"
#include "game/components/damageable.h"
#include "game/components/graphic_rectangular.h"
#include "game/components/idlecontroller.h"

// Using
using ugdk::graphic::Drawable;
using game::base::GameObject;

namespace game {
namespace builder {

ObjectBuilder::ObjectBuilder() {
	TEXT_MANAGER()->AddFont("MAH FONTI", "FUTRFW.ttf", 15, 0, 0);
}

GameObject* ObjectBuilder::BuildHero() {
	GameObject* hero = new GameObject(2,2, new component::GraphicRectangular(L"@"), new component::ControllerPlayer(), new component::Collision("Creature"), new component::Damageable(10.0));
    hero->Initialize();

	Drawable* graphic = TEXT_MANAGER()->GetText(L"@");
    hero->graphic_component()->node()->set_drawable(graphic);

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {
    GameObject* enemy = new GameObject(1,1, new component::GraphicRectangular(L"E"), new component::ControllerAi(), new component::Collision("Creature"), new component::Damageable(4.0));
    enemy->Initialize();

    Drawable* graphic = TEXT_MANAGER()->GetText(L"D");
    enemy->graphic_component()->node()->set_drawable(graphic);

    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {
    GameObject* enemy = new GameObject(1,1, new component::GraphicRectangular(L"I"), new component::ControllerAi(), new component::Collision("Item"), nullptr);

    Drawable* graphic = TEXT_MANAGER()->GetText(L"!");
    enemy->graphic_component()->node()->set_drawable(graphic);

    return enemy;
}

} // namespace builder
} // namespace game