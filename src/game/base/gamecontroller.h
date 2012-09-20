#ifndef BADGAME_BASE_GAMECONTROLLER_H_
#define BADGAME_BASE_GAMECONTROLLER_H_

// Inheritance
#include <ugdk/action/scene.h>

// External Dependencies
#include <cassert>
#include <list>                  // template class, also needed for push_back(-)
#include <vector>                // template class, also needed for size(-)
#include <ugdk/math/integer2D.h> // needed for Tile
#include <ugdk/math/vector2D.h>  // needed for map_size_

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

class GameController : public ugdk::action::Scene {
  typedef ugdk::action::Scene super;
  static const GameController* reference_;

  public:
    static const GameController* reference() { return reference_; }
	static GameController* Initialize() {
		assert(reference_ == nullptr);
		return reference_ == nullptr ? new GameController() : nullptr;
	}
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

    const ugdk::Vector2D& map_size() const { return map_size_; }

    bool TileOutOfBounds(int x, int y) const {
        return y < 0 || y >= tiles_.size() || x < 0 || x >= tiles_[y].size();
    }
    bool TileOutOfBounds(const ugdk::math::Integer2D& coords) const {
        return TileOutOfBounds(coords.x, coords.y);
    }

    GameTile* Tile(int x, int y) const {
        if( !TileOutOfBounds(x,y) )
            return tiles_[y][x];
        return nullptr;
    }
    GameTile* Tile(const ugdk::math::Integer2D& coords) const {
        return Tile(coords.x, coords.y);
    }

    void BlackoutTiles() const;

  private:
    GameController();

    void clearDeadGameObjects();
    void addPendingGameObjects();
    
    std::list<GameObject*> pending_game_objects_;
    std::list<GameObject*> game_objects_;

    ugdk::Vector2D map_size_;
	std::vector< std::vector<GameTile*> > tiles_;

    GameObject* hero_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMECONTROLLER_H_