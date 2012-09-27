// Header File
#include "game/base/gamecontroller.h"

// External Dependencies
#include <cassert>
#include <cstdlib>
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/builder/objectbuilder.h"
#include "game/component/controller_player.h"
#include "game/component/graphic.h"
#include "game/component/shape_rectangular.h"

// Using
using std::list;
using std::vector;
using ugdk::math::Integer2D;
using ugdk::Vector2D;
using game::builder::ObjectBuilder;

namespace game {
namespace base {

/*static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}*/

static bool objectIsDead (const GameObject* value) {
	assert(value != nullptr);
	if( value == nullptr )
		return false;
    bool is_dead = value->dead();
    if (is_dead) {
        delete value;
    }
    return is_dead;
}

GameController* GameController::reference_ = nullptr;

GameController* GameController::reference() {
    return reference_ == nullptr ? new GameController() : reference_;
}

GameController::GameController() : super(), map_size_(500.0, 500.0), hero_(nullptr) {
    reference_ = this;
	TEXT_MANAGER()->AddFont("MAH FONTI", "fonts/FUTRFW.TTF", 15, 0, 0);

	Vector2D pos = Vector2D();
	for(int y = 0; y < 40; ++y) {
		vector<GameTile*> vect;
		pos.x = 0;
		for(int x = 0; x < 50; ++x) {
			GameTile* gt = new GameTile(x, y);
            gt->node()->set_zindex(-1.0);
			gt->node()->modifier()->set_offset(pos);
			content_node()->AddChild(gt->node());
			vect.push_back(gt);

			pos.x += GameTile::TILE_SIZE.x;
		}
		tiles_.push_back(vect);
		pos.y += GameTile::TILE_SIZE.y;
	}

    BlackoutTiles();

    // Time for hard-coded awesomeness to start!
    ObjectBuilder builder = ObjectBuilder();

    // Build the basic instances
    hero_ = builder.BuildHero();
	AddGameObject(hero_);
    GameObject* enemy = builder.BuildEnemy();
	AddGameObject(enemy);
	GameObject* item = builder.BuildItem();
	AddGameObject(item);

    GameObject* wall_1 = builder.BuildWall();
    AddGameObject(wall_1);
    GameObject* wall_2 = builder.BuildWall();
    AddGameObject(wall_2);
    GameObject* wall_3 = builder.BuildWall();
    AddGameObject(wall_3);
    GameObject* wall_4 = builder.BuildWall();
    AddGameObject(wall_4);
    GameObject* wall_5 = builder.BuildWall();
    AddGameObject(wall_5);
    GameObject* wall_6 = builder.BuildWall();
    AddGameObject(wall_6);
    GameObject* wall_7 = builder.BuildWall();
    AddGameObject(wall_7);
    GameObject* wall_8 = builder.BuildWall();
    AddGameObject(wall_8);
    GameObject* wall_9 = builder.BuildWall();
    AddGameObject(wall_9);
    GameObject* wall_0 = builder.BuildWall();
    AddGameObject(wall_0);

    // Add them to the Scene.
    // AddPendingGameObjects() reparents the nodes to the root node,
    //   so we need to call it before placing them on the map.
    addPendingGameObjects();

    // Place them on the map.
    hero_->shape_component()->PlaceAt(Integer2D(10,4));
    enemy->shape_component()->PlaceAt(Integer2D(35,4));
    item->shape_component()->PlaceAt(Integer2D(2,2));
    wall_1->shape_component()->PlaceAt(Integer2D(17,8));
    wall_2->shape_component()->PlaceAt(Integer2D(18,8));
    wall_3->shape_component()->PlaceAt(Integer2D(19,8));
    wall_4->shape_component()->PlaceAt(Integer2D(30,0));
    wall_5->shape_component()->PlaceAt(Integer2D(18,20));
    wall_6->shape_component()->PlaceAt(Integer2D(19,21));
    wall_7->shape_component()->PlaceAt(Integer2D(18,22));
    wall_8->shape_component()->PlaceAt(Integer2D(18,15));
    wall_9->shape_component()->PlaceAt(Integer2D(17,16));
    wall_0->shape_component()->PlaceAt(Integer2D(18,17));
}

GameController::~GameController() {
    if(hero_) delete hero_;
    reference_ = nullptr;
}

void GameController::Update(double dt) {
    // update the entities.
    super::Update(dt);

    if(hero_ && hero_->dead()) {
        Finish();
        return;
    }

    clearDeadGameObjects();
    addPendingGameObjects();
}

void GameController::AddGameObject(GameObject* game_object) {
    pending_game_objects_.push_back(game_object);
}

void GameController::clearDeadGameObjects() {
    for(auto it = game_objects_.begin(); it != game_objects_.end(); ++it) {
        if((*it)->dead())
            RemoveEntity(*it);
    }
    game_objects_.remove_if(objectIsDead);
}

void GameController::BlackoutTiles() {
    for(auto j = tiles_.begin(); j != tiles_.end(); ++j)
        for(auto i = (*j).begin(); i != (*j).end(); ++i)
            (*i)->node()->modifier()->set_visible(false);
}

void GameController::addPendingGameObjects() {
    for(auto it = pending_game_objects_.begin(); it != pending_game_objects_.end(); ++it) {
        if((*it)->graphic_component()->node() != nullptr)
            this->content_node()->AddChild((*it)->graphic_component()->node());
        game_objects_.push_back(*it);
        this->AddEntity(*it);
    }
    pending_game_objects_.clear();
}

} // namespace base
} // namespace game