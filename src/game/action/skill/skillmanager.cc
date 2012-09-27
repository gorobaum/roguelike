
// Header File
#include "game/action/skill/skillmanager.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/action/skill/movement_place.h"
#include "game/action/skill/movement_step.h"
#include "game/action/skill/self_light.h"
#include "game/action/skill/self_selfdamage.h"

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
    Insert(  "see", new      SelfLight());
    Insert( "ouch", new SelfSelfDamage());
}

SkillManager::~SkillManager() {}

} // namespace skill
} // namespace action
} // namespace game
