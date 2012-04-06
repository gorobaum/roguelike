#include <cstdlib>
#include <cmath>
#include <ugdk/time/timeaccumulator.h>
#include "game/components/aicontroller.h"

#include "game/gameobject.h"

namespace game {
namespace component {

#define PI 3.1415926535897932384626433832795

const double AiController::VELOCITY = 100.0;
const double AiController::MIN_WAIT = 2.0;
const double AiController::MAX_WAIT = 5.5;

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

AiController::AiController() : timer_(new ugdk::time::TimeAccumulator(0)) {
}

AiController::~AiController() {
    delete timer_;
}

void AiController::Update(double dt, GameObject* owner) {
    if(timer_->Expired()) {
        
    }
}

} // namespace component
} // namespace game