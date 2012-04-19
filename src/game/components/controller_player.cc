// Header File
#include "game/components/controller_player.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/components/shape.h"

// Using
using ugdk::input::InputManager;
using ugdk::time::TimeAccumulator;
using game::base::GameObject;
using game::action::Movement;

namespace game {
namespace component {

#define DELAY_HOLD 250

ControllerPlayer::ControllerPlayer(GameObject* owner) : super(owner), where_to_(Movement::NONE), time_held_(DELAY_HOLD) {
    time_held_.Pause();
}
ControllerPlayer::~ControllerPlayer() {}

void ControllerPlayer::Update(double dt) {
    InputManager* input = INPUT_MANAGER();

    if( input->KeyPressed(ugdk::input::K_RIGHT) || input->KeyPressed(ugdk::input::K_LEFT) ||
        input->KeyPressed(ugdk::input::K_UP)    || input->KeyPressed(ugdk::input::K_DOWN) ) {

        time_held_.Restart(DELAY_HOLD);

        if(input->KeyPressed(ugdk::input::K_RIGHT)) {
            if(     input->KeyDown(ugdk::input::K_UP)  ) where_to_ = Movement::UP_RIGHT;
            else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Movement::DOWN_RIGHT;
            else where_to_ = Movement::RIGHT;
        }
        else if(input->KeyPressed(ugdk::input::K_LEFT)) {
            if(     input->KeyDown(ugdk::input::K_UP))   where_to_ = Movement::UP_LEFT;
            else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Movement::DOWN_LEFT;
            else where_to_ = Movement::LEFT;
        }
        else if(input->KeyPressed(ugdk::input::K_UP)) {
            if(     input->KeyDown(ugdk::input::K_LEFT) ) where_to_ = Movement::UP_LEFT;
            else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Movement::UP_RIGHT;
            else where_to_ = Movement::UP;
        }
        else { // if(input->KeyPressed(ugdk::input::K_DOWN)) {
            if(     input->KeyDown(ugdk::input::K_LEFT) ) where_to_ = Movement::DOWN_LEFT;
            else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Movement::DOWN_RIGHT;
            else where_to_ = Movement::DOWN;
        }
    }

    if( input->KeyReleased(ugdk::input::K_RIGHT) || input->KeyReleased(ugdk::input::K_LEFT) ||
        input->KeyReleased(ugdk::input::K_UP)    || input->KeyReleased(ugdk::input::K_DOWN) ) {
        
        time_held_.Restart(DELAY_HOLD);
        time_held_.Pause();
        owner_->shape_component()->Step(where_to_);
        where_to_ = Movement::NONE;
    }
    else if ( ( input->KeyDown(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_LEFT) ||
                input->KeyDown(ugdk::input::K_UP)    || input->KeyDown(ugdk::input::K_DOWN) )
              && time_held_.Expired() ) {

        if(where_to_ != Movement::NONE) owner_->shape_component()->Step(where_to_);
    }
}

} // namespace component
} // namespace game