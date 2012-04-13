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
	ObjectBuilder builder;
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

	hero_ = builder.BuildHero();
    hero_->shape_component()->PlaceAt(tiles_[5][6]);
	this->AddEntity(hero_);

    //ugdk::graphic::SolidRectangle* background_rect = new ugdk::graphic::SolidRectangle(map_size_);
    //content_node()->set_drawable(background_rect);

    GameObject* enemy = builder.BuildEnemy();
    enemy->shape_component()->PlaceAt(tiles_[3][3]);
	this->AddEntity(enemy);

	GameObject* item = builder.BuildItem();
    item->shape_component()->PlaceAt(tiles_[2][2]);
	this->AddEntity(item);
}

GameController::~GameController() {
    if(hero_ != nullptr) delete hero_;
}

void GameController::HandleCollisions() {
/*    std::list<CollisionInstance> collision_list;
    
    // Update objects positions in CollisionManager
    pyramidworks::collision::CollisionManager::reference()->Update();

    GameObjectList::iterator i;
    for (i = game_objects_.begin(); i != game_objects_.end(); ++i)
        (*i)->collision_object()->SearchCollisions(collision_list);

    std::list<CollisionInstance>::iterator it;
    for(it = collision_list.begin(); it != collision_list.end(); ++it) {
        it->first->Handle(it->second);
    }
*/
}

void GameController::Update(double dt) {
    super::Update(dt);

    if(hero_ && hero_->dead()) {
        Finish();
        return;
    }

    //TODO: Fix?
    /*
	for(auto yt = tiles_.begin(); yt != tiles_.end(); ++yt)
		for(auto xt = yt->begin(); xt != yt->end(); ++xt)
			(*xt)->UpdateNode();

	for(auto yt = tiles_.begin(); yt != tiles_.end(); ++yt)
		for(auto xt = yt->begin(); xt != yt->end(); ++xt)
			(*xt)->set_update_node_flag(false);
    */

    ClearDeadGameObjects();
    AddPendingGameObjects();
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

        //new_obj->set_game_controller(this);
        //new_obj->collision_object()->StartColliding();
    }
    pending_game_objects_.clear();
}

GameTile* GameController::GetTileByMovementFromTile(GameTile* tile, Movement& mov) const {
	if(tile == nullptr) return tile;
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
	if(y < 0 || y >= static_cast<size_t>(tiles_.size())) return NULL;
	if(x < 0 || x >= static_cast<size_t>(tiles_[y].size())) return NULL;
	return GetTileFromCoordinates(x,y);
}

} // namespace base
} // namespace game