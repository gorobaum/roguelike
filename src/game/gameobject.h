#ifndef BADGAME_GAMEOBJECT_H_
#define BADGAME_GAMEOBJECT_H_

#include <list>

#include <ugdk/action/entity.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time.h>

#include "game/component.h"
#include "game.h"

namespace game {

class GameObject : public ugdk::Entity {
  typedef ugdk::Entity super;
  public:
	GameObject(component::Graphic*, component::Controller* controller, component::Collision* collision, component::Damageable* = nullptr);
    ~GameObject();

    void Update(double dt);

	void UpdateNode();

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Damageable* damageable_component() { return damageable_component_; }
	component::Collision*   collision_component() { return  collision_component_; }

    void set_world_position(const ugdk::Vector2D& position);
    const ugdk::Vector2D& world_position() const { return world_position_; }

    void Die() { dead_ = true; }
    bool dead() const { return dead_; }

    GameController* game_controller() { return game_controller_; }
    void set_game_controller(GameController* game) { game_controller_ = game; }

    void set_timed_life(ugdk::time::TimeAccumulator* timed_life) { timed_life_ = timed_life; }

	//void MoveTo(GameTile*);

	//GameTile* GameObject::game_tile();

  private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
    component::Collision*   collision_component_;
    component::Damageable* damageable_component_;
    
    ugdk::time::TimeAccumulator* timed_life_;
    ugdk::Vector2D world_position_;
    bool dead_;
    GameController* game_controller_;
public: //TODO: OHNOHOWCOULDTHISHAPPEN
	std::list<GameTile*> occupying_tiles_;
private:
};

} // namespace game

#endif // BADGAME_GAMEOBJECT_H_