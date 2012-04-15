// Header File
#include "game/builders/objectbuilder.h"

// External Dependencies
#include <string>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/controller_ai.h"
#include "game/components/controller_idle.h"
#include "game/components/controller_player.h"
#include "game/components/collision.h"
#include "game/components/damageable.h"
#include "game/components/shape_rectangular.h"
#include "game/components/graphic_rectangular.h"

// Using
using game::base::GameObject;
using game::component::Collision;
using game::component::ControllerAi;
using game::component::ControllerIdle;
using game::component::ControllerPlayer;
using game::component::Damageable;
using game::component::GraphicRectangular;
using game::component::ShapeRectangular;

namespace game {
namespace builder {

GameObject* ObjectBuilder::BuildHero() {

    GameObject* hero = new GameObject();
    hero->Initialize(
        new   ControllerPlayer(hero),
        new          Collision(hero, "Creature"),
        new         Damageable(hero, 10.0),
        new   ShapeRectangular(hero, 2, 2),
        new GraphicRectangular(hero, L"@", 3.0)
    );

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {

    GameObject* enemy = new GameObject();
    enemy->Initialize(
        new       ControllerAi(enemy),
        new          Collision(enemy, "Creature"),
        new         Damageable(enemy, 4.0),
        new   ShapeRectangular(enemy, 5, 6),
        new GraphicRectangular(enemy, L"E", 2.0)
    );

    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {

    GameObject* item = new GameObject();
    item->Initialize(
        new     ControllerIdle(item),
        new          Collision(item, "Item"),
        nullptr,
        new   ShapeRectangular(item, 1, 1),
        new GraphicRectangular(item, L"i", 1.0)
    );

    return item;
}

} // namespace builder
} // namespace game