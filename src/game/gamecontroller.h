#ifndef BADGAME_GAMECONTROLLER_H_
#define BADGAME_GAMECONTROLLER_H_

#include <list>
#include <vector>
#include <ugdk/action/scene.h>
#include <ugdk/time.h>

namespace game {

class GameTile;
class GameObject;

struct Movement {
	enum Direction {
		UP, DOWN, RIGHT, LEFT
	};

	std::list<Direction> dirs;
};

class GameController : public ugdk::Scene {
  typedef ugdk::Scene super;
  public:
	static GameController* reference_; //TODO: MANO,NAO.

    GameController();
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

    const ugdk::Vector2D& map_size() const { return map_size_; }

	GameTile* GetTileByMovementFromTile(GameTile*, Movement&);
	GameTile* GetTileByDirectionFromTile(GameTile* tile, Movement::Direction d) {
		Movement m;
		m.dirs.push_back(d);
		return GetTileByMovementFromTile(tile, m);
	}

    GameTile* GetTileFromCoordinates(int x, int y) {
        if( 0 <= y && y < tiles_.size() && 0 <= x && x < tiles_[y].size() )
            return tiles_[y][x];
        return nullptr;
    }

  private:
    typedef std::list<GameObject*> GameObjectList;
    void HandleCollisions();
    void ClearDeadGameObjects();
    void AddPendingGameObjects();

    ugdk::Vector2D map_size_;
    GameObject* hero_;
	std::vector< std::vector<GameTile*> > tiles_;
private:
    GameObjectList game_objects_;
    GameObjectList pending_game_objects_;
};

} // namespace game

#endif // BADGAME_GAMECONTROLLER_H_