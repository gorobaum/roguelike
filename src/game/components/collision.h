#ifndef BADGAME_COMPONENT_COLLISION_H_
#define BADGAME_COMPONENT_COLLISION_H_

#include <ugdk/graphic.h>
#include <string>

namespace game {

class GameObject;

namespace component {

class Collision {
  public:
    Collision(std::string collision_class) : owner_(nullptr), collision_class_(collision_class) {}
    ~Collision() {}

    void set_owner(GameObject* owner) { owner_ = owner; } //TODO: Mudar para ser no construtor

	void Update(double dt, GameObject* owner) {};
	void Handle(GameObject* collider);
	std::string CollisionClass() { return collision_class_; };

  protected:
    GameObject* owner_;

  private:
    std::string collision_class_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_COLLISION_H_