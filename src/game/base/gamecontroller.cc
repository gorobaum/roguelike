// Header File
#include "game/base/gamecontroller.h"

// External Dependencies
#include <cstdlib>

#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time/timeaccumulator.h>

// Internal Dependencies
#include "game/action/movement.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/builders/objectbuilder.h"
#include "game/components/controller_player.h"
#include "game/components/graphic.h"
#include "game/components/shape_rectangular.h"

// Using
using std::list;
using std::vector;
using ugdk::Vector2D;
using game::builder::ObjectBuilder;
using game::action::Movement;

namespace game {
namespace base {

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

static bool objectIsDead (const GameObject* value) {
    bool is_dead = value->dead();
    if (is_dead) {
        delete value;
    }
    return is_dead;
}

const GameController* GameController::reference_ = nullptr;

GameController::GameController() : super(), map_size_(500.0, 500.0), hero_(nullptr) {
	reference_ = this;
	Vector2D pos;
    ObjectBuilder builder; // Initializes the font.

	for(size_t y = 0; y < 35; ++y) {
		vector<GameTile*> vect;
		pos.x = 0;
		for(size_t x = 0; x < 45; ++x) {
			GameTile* gt = new GameTile(x, y);
			gt->node()->modifier()->set_offset(pos);
			content_node()->AddChild(gt->node());
			vect.push_back(gt);

			pos.x += GameTile::TILE_SIZE.x;
		}
		tiles_.push_back(vect);
		pos.y += GameTile::TILE_SIZE.y;
	}

    // Build the basic instances
    hero_ = builder.BuildHero();
	AddGameObject(hero_);
    GameObject* enemy = builder.BuildEnemy();
	AddGameObject(enemy);
	GameObject* item = builder.BuildItem();
	AddGameObject(item);

    // Add them to the Scene.
    // AddPendingGameObjects(-) reparents the nodes to the root node,
    //   so we need to call it before placing them on the map.
    AddPendingGameObjects();

    // Place them on the map.
    hero_->shape_component()->PlaceAt(tiles_[5][6]);
    enemy->shape_component()->PlaceAt(tiles_[3][3]);
    item->shape_component()->PlaceAt(tiles_[2][2]);
}

GameController::~GameController() {
    if(hero_ != nullptr) delete hero_;
}

void GameController::Update(double dt) {
    super::Update(dt);

    if(hero_ && hero_->dead()) {
        Finish();
        return;
    }

    ClearDeadGameObjects();
    AddPendingGameObjects();
    
    for(auto it = game_objects_.begin(); it != game_objects_.end(); ++it)
        (*it)->Update(dt);
}

void GameController::AddGameObject(GameObject* game_object) {
    pending_game_objects_.push_back(game_object);
}

void GameController::ClearDeadGameObjects() {
    for(list<GameObject*>::iterator it = game_objects_.begin(); it != game_objects_.end(); ++it) {
        if((*it)->dead())
            RemoveEntity(*it);
    }
    game_objects_.remove_if(objectIsDead);
}

void GameController::AddPendingGameObjects() {
    for(auto it = pending_game_objects_.begin(); it != pending_game_objects_.end(); ++it) {
        GameObject* new_obj = *it;
        if(new_obj->graphic_component()->node() != nullptr)
            this->content_node()->AddChild(new_obj->graphic_component()->node());
        game_objects_.push_back(new_obj);
        this->AddEntity(new_obj);
    }
    pending_game_objects_.clear();
}

GameTile* GameController::GetTileByMovementFromTile(GameTile* tile, Movement& mov) const {
	if(tile == nullptr) return nullptr;
	size_t x = tile->x(), y = tile->y();
	for(auto it = mov.dirs.begin(); it != mov.dirs.end(); ++it) {
		switch(*it) {
			case Movement::UP:    --y; break;
			case Movement::DOWN:  ++y; break;
			case Movement::LEFT:  --x; break;
			case Movement::RIGHT: ++x; break;
			default: break;
		}
	}
	if(y < 0 || y >= static_cast<size_t>(tiles_.size())) return nullptr;
	if(x < 0 || x >= static_cast<size_t>(tiles_[y].size())) return nullptr;
	return GetTileFromCoordinates(x,y);
}

} // namespace base
} // namespace game