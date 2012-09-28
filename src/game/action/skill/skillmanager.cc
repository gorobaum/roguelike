
// Header File
#include "game/action/skill/skillmanager.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/skill/movement_place.h"
#include "game/action/skill/movement_step.h"
#include "game/action/skill/self_lightvision.h"
#include "game/action/skill/self_damage.h"

// Using
// (none)

namespace game {
namespace action {
namespace skill {

// singleton
SkillManager* SkillManager::reference_ = nullptr;


SkillManager::SkillManager() {
    Insert("place", new MovementPlace());
    Insert( "step", new   MovementStep());
    Insert(  "see", new      LightVision());
    Insert( "ouch", new SelfDamage());
}

SkillManager::~SkillManager() {}

} // namespace skill
} // namespace action
} // namespace game
