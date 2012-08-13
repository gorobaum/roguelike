#ifndef BADGAME_BASE_GAMETILE_H_
#define BADGAME_BASE_GAMETILE_H_

// Inheritance
// (none)

// External Dependencies
#include <list> // template class
#include <ugdk/math/integer2D.h> // coords_

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include "game/base.h"

namespace game {
namespace base {

class GameTile {
  public:
	static const ugdk::Vector2D TILE_SIZE;

	GameTile(int x, int y);
    GameTile(const ugdk::math::Integer2D& coords);
	~GameTile();

	ugdk::graphic::Node* node() const { return node_; }

	void PushObject(GameObject* obj);
	void RemoveObject(GameObject* obj);

	
	int x() const { return coords_.x; }
	int y() const { return coords_.y; }

    const ugdk::math::Integer2D& coords() const { return coords_; }

	ugdk::graphic::Node* node() { return node_; }
    const std::list<GameObject*>& objects_here() const { return objects_here_; }

  private:
	ugdk::graphic::Node* node_;
	std::list<GameObject*> objects_here_;
	ugdk::graphic::Drawable* ground_;

	ugdk::math::Integer2D coords_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMETILE_H_