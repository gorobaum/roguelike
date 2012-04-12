#ifndef BADGAME_COMPONENT_COLLISION_H_
#define BADGAME_COMPONENT_COLLISION_H_

// Inheritance
// (none)

// External Dependencies
#include <string>   // can't forward-declare std::string;

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Collision {
  public:
    Collision(std::string collision_class) : owner_(nullptr), collision_class_(collision_class) {}
    ~Collision() {}

    void set_owner(game::base::GameObject* owner) { owner_ = owner; } //TODO: Mudar para ser no construtor

	void Update(double dt, game::base::GameObject* owner) {};
	void Handle(game::base::GameObject* collider);
	std::string CollisionClass() { return collision_class_; };

  protected:
    game::base::GameObject* owner_;

  private:
    std::string collision_class_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_COLLISION_H_