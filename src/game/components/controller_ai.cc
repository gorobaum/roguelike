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

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

void ControllerAi::Update(double dt) {

}

} // namespace component
} // namespace game