
// Header File
#include "game/action/skill/generic.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gamething.h"

// Using
using game::action::skill::GameTargets;
using game::base::GameThing;

namespace game {
namespace action {
namespace skill {
    
Generic::Generic(const GenericValidator& validator, const GenericSpender& spender, const GameAction& action)
  : validator_(validator), spender_(spender), action_(action) {}


bool Generic::operator()(base::GameObject* caster, const GameTargets& targets) {

    if(validator_(caster,targets)) {
        double power = spender_(caster,targets);
        if( power != 0.0 ) {
            action_(caster,targets,power);
            return true;
        }
    }

    return false;
}

} // namespace skill
} // namespace action
} // namespace game
