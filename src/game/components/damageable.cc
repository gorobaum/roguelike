// Header File
#include "game/components/damageable.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using game::base::GameObject;

namespace game {
namespace component {

void Damageable::Update(double dt, GameObject* owner) {
    if(current_life_ < 0.0) {
        owner->Die();
    }
}

} // namespace component
} // namespace game