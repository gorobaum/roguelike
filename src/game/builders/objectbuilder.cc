// Header File
#include "game/builders/objectbuilder.h"

// External Dependencies
#include <string>
#include <limits>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/components/controller_ai.h"
#include "game/components/controller_idle.h"
#include "game/components/controller_player.h"
#include "game/components/damageable.h"
#include "game/components/shape_rectangular.h"
#include "game/components/graphic_rectangular.h"

// Using
using std::numeric_limits;
using game::base::GameObject;
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
        new         Damageable(hero, 10.0),
        new   ShapeRectangular(hero, 2, 2, 1.0, 0.25, 1.0e-6),
        new GraphicRectangular(hero, "@", 3.0)
    );

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {

    GameObject* enemy = new GameObject();
    enemy->Initialize(
        new       ControllerAi(enemy),
        new         Damageable(enemy, 4.0),
        new   ShapeRectangular(enemy, 5, 6, 3.0, 0.8, 1.0e-6),
        new GraphicRectangular(enemy, "E", 2.0)
    );

    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {

    GameObject* item = new GameObject();
    item->Initialize(
        new     ControllerIdle(item),
        nullptr,
        new   ShapeRectangular(item, 1, 1, 0.1, 0.025, 0.0),
        new GraphicRectangular(item, "!", 1.0)
    );

    return item;
}

GameObject* ObjectBuilder::BuildWall() {

    GameObject* wall = new GameObject();
    wall->Initialize(
        new     ControllerIdle(wall),
        nullptr,
        new   ShapeRectangular(wall, 1, 1, numeric_limits<double>::infinity(), 0.0, 0.0 ),
        new GraphicRectangular(wall, "null", 1.0)
    );

    return wall;
}

} // namespace builder
} // namespace game