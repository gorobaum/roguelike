// Header File
#include "game/components/collision.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Using
using std::string;
using game::base::GameObject;

namespace game {
namespace component {

Collision::Collision(GameObject* owner, string collision_class)
  : super(owner), collision_class_(collision_class) {}
Collision::~Collision() {}

void Collision::Update(double dt) {

}

void Collision::Handle(GameObject* collider) {

}

} // namespace component
} // namespace game