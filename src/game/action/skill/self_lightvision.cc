
// Header File
#include "game/action/skill/self_lightvision.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/vision.h"

// Using
using game::base::GameObject;

namespace game {
namespace action {
namespace skill {

static double spend_sense_lightvision(GameObject* caster) {
    return 1.0;
}

static void act_sense_lightvision(GameObject* caster, double power) {
    caster->vision_component()->See();
}

LightVision::LightVision()
  : super(spend_sense_lightvision, act_sense_lightvision) {}

} // namespace skill
} // namespace action
} // namespace game
