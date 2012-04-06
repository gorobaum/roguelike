#ifndef BADGAME_GAMETILE_H_
#define BADGAME_GAMETILE_H_

#include <list>
#include <ugdk/graphic.h>
#include <ugdk/math/vector2D.h>
#include "game.h"

namespace game {

class GameTile  {
  public:
	GameTile(int x, int y);
	~GameTile();

	static const ugdk::Vector2D TILE_SIZE;

	ugdk::graphic::Node* node() const { return node_; }

	void UpdateNode();

	void PushObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	
	//void Collide(GameObject* obj);

	//void set_position(int x, int y) { x_ = x; y_ = y; }
	int x() const { return x_; }
	int y() const { return y_; }

	bool update_node_flag() const { return update_node_flag_; }
	void set_update_node_flag(const bool value) { update_node_flag_ = value; }

	ugdk::graphic::Node* node() { return node_; }

  private:
	ugdk::graphic::Node* node_;
	std::list<GameObject*> objects_here_;
	ugdk::graphic::Drawable* ground_;

	int x_, y_;

	bool update_node_flag_;
};

} // namespace game

#endif // BADGAME_GAMEOBJECT_H_