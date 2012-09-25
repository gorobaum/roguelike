
// Header File
#include "game/action/time/timemanager.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/energy.h"

// Using
using game::base::GameObject;
using game::component::Energy;

namespace game {
namespace action {
namespace time {

bool obj_less::operator()(const GameObject* a, const GameObject* b) const {
    const Energy* enga = a->energy_component();
    if(enga == nullptr) return true;
    const Energy* engb = b->energy_component();
    if(engb == nullptr) return false;
    return enga->Mean() < engb->Mean();
}

// singleton
TimeManager* TimeManager::reference_ = nullptr;

} // namespace time
} // namespace action
} // namespace game
