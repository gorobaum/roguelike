#include "game/components/damageable.h"

#include "game/base/gameobject.h"

namespace game {
namespace component {

void Damageable::Update(double dt, GameObject* owner) {
    if(current_life_ < 0.0) {
        owner->Die();
    }
}

} // namespace component
} // namespace game