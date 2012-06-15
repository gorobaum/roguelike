// Header File
#include "game/components/damageable.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
// (none)

namespace game {
namespace component {

void Damageable::TakeDamage(double dmg) {
    current_life_ -= dmg;
    if(current_life_ <= 0.0) StartToDie();
}

void Damageable::StartToDie() {
    owner_->Die();
}

} // namespace component
} // namespace game