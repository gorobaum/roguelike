#ifndef BADGAME_BASE_GAMECONTROLLER_H_
#define BADGAME_BASE_GAMECONTROLLER_H_

// Inheritance
#include <ugdk/action/scene.h>

// External Dependencies
#include <list>      // template class, also needed for push_back(-)
#include <vector>    // template class, also needed for size(-)

#include <ugdk/math/vector2D.h>

// Internal Dependencies

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

struct Movement {
	enum Direction {
		UP, DOWN, RIGHT, LEFT
	};

	std::list<Direction> dirs;
};

class GameController : public ugdk::Scene {
  typedef ugdk::Scene super;
  public:
	static const GameController* reference_; //TODO: Pelo menos é const neh...

    GameController();
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

    const ugdk::Vector2D& map_size() const { return map_size_; }

	GameTile* GetTileByMovementFromTile(GameTile*, Movement&) const;
	GameTile* GetTileByDirectionFromTile(GameTile* tile, Movement::Direction d) {
		Movement m;
		m.dirs.push_back(d);
		return GetTileByMovementFromTile(tile, m);
	}

    GameTile* GetTileFromCoordinates(size_t x, size_t y) const {
        if( 0 <= y && y < tiles_.size() && 0 <= x && x < tiles_[y].size() )
            return tiles_[y][x];
        return nullptr;
    }

  private:
    void HandleCollisions();
    void ClearDeadGameObjects();
    void AddPendingGameObjects();

    ugdk::Vector2D map_size_;
    GameObject* hero_;
	std::vector< std::vector<GameTile*> > tiles_;

    std::list<GameObject*> game_objects_;
    std::list<GameObject*> pending_game_objects_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMECONTROLLER_H_