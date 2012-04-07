#include <ugdk/base/engine.h>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/textmanager.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/math/vector2D.h>

#include "game/builders/objectbuilder.h"

#include "game/gameobject.h"
#include "game/components/graphic_rectangular.h"
#include "game/components/damageable.h"
#include "game/components/collision.h"
#include "game/components/playercontroller.h"
#include "game/components/aicontroller.h"
#include "game/components/idlecontroller.h"

#include "game/gamecontroller.h"

#include "game/gametile.h"

namespace game {
namespace builder {

ObjectBuilder::ObjectBuilder() {
	TEXT_MANAGER()->AddFont("MAH FONTI", "FUTRFW.ttf", 30, 0, 0);
}

GameObject* ObjectBuilder::BuildHero() {
	GameObject* hero = new GameObject(new component::GraphicRectangular(L"@", 2, 2), new component::PlayerController, new component::Collision("Creature"), new component::Damageable(10.0));
	
	ugdk::graphic::Drawable* graphic = TEXT_MANAGER()->GetText(L"@");
    //graphic->set_hotspot(ugdk::graphic::Drawable::CENTER);
    hero->graphic_component()->node()->set_drawable(graphic);

	//TODO: ISSOAQUIÈTESTE
	hero->occupying_tiles_.push_back(game::GameController::reference_->tiles_[2][2]);
	hero->occupying_tiles_.push_back(game::GameController::reference_->tiles_[2][3]);
	hero->occupying_tiles_.push_back(game::GameController::reference_->tiles_[3][2]);
	hero->occupying_tiles_.push_back(game::GameController::reference_->tiles_[3][3]);
	game::GameController::reference_->tiles_[2][2]->PushObject(hero);
    game::GameController::reference_->tiles_[2][3]->PushObject(hero);
	game::GameController::reference_->tiles_[3][2]->PushObject(hero);
	game::GameController::reference_->tiles_[3][3]->PushObject(hero);

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {
    GameObject* enemy = new GameObject(new component::GraphicRectangular(L"E", 1, 1), new component::AiController, new component::Collision("Creature"), new component::Damageable(4.0));

    ugdk::graphic::Drawable* graphic = TEXT_MANAGER()->GetText(L"D");
    enemy->graphic_component()->node()->set_drawable(graphic);

    return enemy;
}

GameObject* ObjectBuilder::BuildItem() {
    GameObject* enemy = new GameObject(new component::GraphicRectangular(L"I", 1, 1), new component::AiController, new component::Collision("Item"), nullptr);

    ugdk::graphic::Drawable* graphic = TEXT_MANAGER()->GetText(L"!");
    enemy->graphic_component()->node()->set_drawable(graphic);

    return enemy;
}

} // namespace builder
} // namespace game