#ifndef BADGAME_BASE_GAMETILE_H_
#define BADGAME_BASE_GAMETILE_H_

// Inheritance
// (none)

// External Dependencies
#include <list> // template class

// Internal Dependencies

// Forward Declarations
#include <ugdk/graphic.h>
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace base {

class GameTile  {
  public:
	GameTile(size_t x, size_t y);
	~GameTile();

	static const ugdk::Vector2D TILE_SIZE;

	ugdk::graphic::Node* node() const { return node_; }

	void UpdateNode();

	void PushObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	
	//void Collide(GameObject* obj);

	//void set_position(size_t x, size_t y) { x_ = x; y_ = y; }
	size_t x() const { return x_; }
	size_t y() const { return y_; }

	bool update_node_flag() const { return update_node_flag_; }
	void set_update_node_flag(const bool value) { update_node_flag_ = value; }

	ugdk::graphic::Node* node() { return node_; }

  private:
	ugdk::graphic::Node* node_;
	std::list<GameObject*> objects_here_;
	ugdk::graphic::Drawable* ground_;

	size_t x_, y_;

	bool update_node_flag_;
};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMEOBJECT_H_