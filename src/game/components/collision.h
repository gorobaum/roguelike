#ifndef BADGAME_COMPONENT_COLLISION_H_
#define BADGAME_COMPONENT_COLLISION_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
#include <string>   // can't forward-declare std::wstring;

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Collision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Collision(game::base::GameObject* owner, std::string collision_class);
    ~Collision();

	void Update(double dt);

	void Handle(game::base::GameObject* collider);

	const std::string CollisionClass() const { return collision_class_; };

  private:
    std::string collision_class_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_COLLISION_H_