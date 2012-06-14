#ifndef BADGAME_BASE_GAMETILE_H_
#define BADGAME_BASE_GAMETILE_H_

// Inheritance
// (none)

// External Dependencies
#include <list> // template class

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace base {

class GameTile {
  public:
	static const ugdk::Vector2D TILE_SIZE;

	GameTile(size_t x, size_t y);
	~GameTile();

	ugdk::graphic::Node* node() const { return node_; }

	void PushObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	
	size_t x() const { return x_; }
	size_t y() const { return y_; }

	ugdk::graphic::Node* node() { return node_; }
    const std::list<GameObject*>& objects_here() const { return objects_here_; }

  private:
	ugdk::graphic::Node* node_;
	std::list<GameObject*> objects_here_;
	ugdk::graphic::Drawable* ground_;

	size_t x_, y_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMEOBJECT_H_