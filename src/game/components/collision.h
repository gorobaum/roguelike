#ifndef BADGAME_COMPONENT_COLLISION_H_
#define BADGAME_COMPONENT_COLLISION_H_

#include <ugdk/graphic.h>
#include <string>
#include "game.h"

namespace game {
namespace component {

class Collision {
  //typedef ugdk::Scene super;
  public:
    Collision(std::string collision_class) : collision_class_(collision_class) {}
    ~Collision() {}

	void Update(double dt, GameObject* owner) {};
	void Handle(GameObject* collider);
	std::string CollisionClass() { return collision_class_; };

  private:
    std::string collision_class_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_COLLISION_H_