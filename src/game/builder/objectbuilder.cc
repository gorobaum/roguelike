// Header File
#include "game/builder/objectbuilder.h"

// External Dependencies
#include <string>
#include <limits>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/controller_ai.h"
#include "game/component/controller_idle.h"
#include "game/component/controller_player.h"
#include "game/component/vision.h"
#include "game/component/damageable.h"
#include "game/component/shape_rectangular.h"
#include "game/component/graphic_rectangular.h"

// Using
using std::numeric_limits;
using game::base::GameObject;
using game::component::ControllerAi;
using game::component::ControllerIdle;
using game::component::ControllerPlayer;
using game::component::Vision;
using game::component::ShapeRectangular;
using game::component::Damageable;
using game::component::GraphicRectangular;

namespace game {
namespace builder {

GameObject* ObjectBuilder::BuildHero() {

    GameObject* hero = new GameObject();
    hero->Initialize(
        new   ControllerPlayer(hero),
        new             Vision(hero),
        new         Damageable(hero, 10.0),
        new   ShapeRectangular(hero, 1, 1, 1.0, 0.25, 1.0e-9),
        new GraphicRectangular(hero, "@", 3.0)
    );

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {

    GameObject* enemy = new GameObject();
    enemy->Initialize(
        new       ControllerAi(enemy),
        /*new             Vision(enemy),*/nullptr,
        new         Damageable(enemy, 4.0),
        new   ShapeRectangular(enemy, 5, 6, 3.0, 0.8, 1.0e-9),
        new GraphicRectangular(enemy, "E", 2.0)
    );

    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {

    GameObject* item = new GameObject();
    item->Initialize(
        new     ControllerIdle(item),
        nullptr,
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
        nullptr,
        new   ShapeRectangular(wall, 1, 1, numeric_limits<double>::infinity(), 0.0, 0.0 ),
        new GraphicRectangular(wall, "null", 1.0)
    );

    return wall;
}

} // namespace builder
} // namespace game