// Header File
#include "game/base/gameobject.h"

// External Dependencies
#include <cmath>
#include <cstdlib>

#include <ugdk/time/timeaccumulator.h>

// Internal Dependencies
#include "game/components/controller_ai.h"

// Using
using game::base::GameObject;

namespace game {
namespace component {

#define PI 3.1415926535897932384626433832795

const double ControllerAi::VELOCITY = 100.0;
const double ControllerAi::MIN_WAIT = 2.0;
const double ControllerAi::MAX_WAIT = 5.5;

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

void ControllerAi::Update(double dt, GameObject* owner) {
    if(timer_->Expired()) {
        
    }
}

} // namespace component
} // namespace game