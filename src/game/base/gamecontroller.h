#ifndef BADGAME_BASE_GAMECONTROLLER_H_
#define BADGAME_BASE_GAMECONTROLLER_H_

// Inheritance
#include <ugdk/action/scene.h>

// External Dependencies
#include <list>                 // template class, also needed for push_back(-)
#include <vector>               // template class, also needed for size(-)
#include <ugdk/math/vector2D.h> // needed for map_size_

// Internal Dependencies
#include "game/action/movement.h" // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

class GameController : public ugdk::Scene {
  typedef ugdk::Scene super;
  static const GameController* reference_;

  public:
    static const GameController* reference() { return reference_; }

    GameController();
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

    const ugdk::Vector2D& map_size() const { return map_size_; }

    GameTile* GetTileFromCoordinates(size_t x, size_t y) const {
        if( 0 <= y && y < tiles_.size() && 0 <= x && x < tiles_[y].size() )
            return tiles_[y][x];
        return nullptr;
    }
	GameTile* GetTileByMovementFromTile(GameTile* tile, game::action::Movement&) const;
	GameTile* GetTileByDirectionFromTile(GameTile* tile, game::action::Movement::Direction d) const {
		game::action::Movement m;
		m.dirs.push_back(d);
		return GetTileByMovementFromTile(tile, m);
	}


  private:
    void ClearDeadGameObjects();
    void AddPendingGameObjects();
    
    std::list<GameObject*> pending_game_objects_;
    std::list<GameObject*> game_objects_;

    ugdk::Vector2D map_size_;
	std::vector< std::vector<GameTile*> > tiles_;

    GameObject* hero_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMECONTROLLER_H_