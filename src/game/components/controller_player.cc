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
using game::base::GameObject;
using game::action::Movement;

namespace game {
namespace component {

ControllerPlayer::ControllerPlayer(GameObject* owner) : super(owner), where_to_(Movement::NONE), special_(false) {}
ControllerPlayer::~ControllerPlayer() {}

void ControllerPlayer::Update(double dt) {
    InputManager* input = INPUT_MANAGER();

    if(input->KeyPressed(ugdk::input::K_RIGHT))
        switch(where_to_) {
            case Movement::NONE:
                if(input->KeyDown(ugdk::input::K_UP)) where_to_ = Movement::UP_RIGHT;
                else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Movement::DOWN_RIGHT;
                else where_to_ = Movement::RIGHT;
                break;
            case Movement::UP:    where_to_ = Movement::UP_RIGHT;   break;
            case Movement::DOWN:  where_to_ = Movement::DOWN_RIGHT; break;
            case Movement::LEFT:  where_to_ = Movement::LEFT;       break;
            default: break;
        }
    else if(input->KeyPressed(ugdk::input::K_LEFT))
        switch(where_to_) {
            case Movement::NONE:
                if(input->KeyDown(ugdk::input::K_UP)) where_to_ = Movement::UP_LEFT;
                else if(input->KeyDown(ugdk::input::K_DOWN)) where_to_ = Movement::DOWN_LEFT;
                else where_to_ = Movement::LEFT;
                break;
            case Movement::UP:    where_to_ = Movement::UP_LEFT;    break;
            case Movement::DOWN:  where_to_ = Movement::DOWN_LEFT;  break;
            case Movement::RIGHT: where_to_ = Movement::RIGHT;      break;
            default: break;
        }
    else if(input->KeyPressed(ugdk::input::K_UP))
        switch(where_to_) {
            case Movement::NONE:
                if(input->KeyDown(ugdk::input::K_LEFT)) where_to_ = Movement::UP_LEFT;
                else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Movement::UP_RIGHT;
                else where_to_ = Movement::UP;
                break;
            case Movement::DOWN:  where_to_ = Movement::DOWN;       break;
            case Movement::LEFT:  where_to_ = Movement::UP_LEFT;    break;
            case Movement::RIGHT: where_to_ = Movement::UP_RIGHT;   break;
            default: break;
        }
    else if(input->KeyPressed(ugdk::input::K_DOWN))
        switch(where_to_) {
            case Movement::NONE:
                if(input->KeyDown(ugdk::input::K_LEFT)) where_to_ = Movement::DOWN_LEFT;
                else if(input->KeyDown(ugdk::input::K_RIGHT)) where_to_ = Movement::DOWN_RIGHT;
                else where_to_ = Movement::DOWN;
                break;
            case Movement::UP:    where_to_ = Movement::UP;         break;
            case Movement::LEFT:  where_to_ = Movement::DOWN_LEFT;  break;
            case Movement::RIGHT: where_to_ = Movement::DOWN_RIGHT; break;
            default: break;
        }

    if(input->KeyReleased(ugdk::input::K_RIGHT) || input->KeyReleased(ugdk::input::K_LEFT) ||
        input->KeyReleased(ugdk::input::K_UP)    || input->KeyReleased(ugdk::input::K_DOWN)) {
        
        owner_->shape_component()->Step(where_to_);
        where_to_ = Movement::NONE;
    }

    /*
	Movement mov;


    if(input->KeyPressed(ugdk::input::K_RIGHT))
		dir = Movement::RIGHT;
	else if(input->KeyPressed(ugdk::input::K_LEFT) || input->KeyDown(ugdk::input::K_a))
		mov.dirs.push_back(Movement::LEFT);
    else if(input->KeyPressed(ugdk::input::K_UP)   || input->KeyDown(ugdk::input::K_w))
		mov.dirs.push_back(Movement::UP);
    else if(input->KeyPressed(ugdk::input::K_DOWN) || input->KeyDown(ugdk::input::K_s))
		mov.dirs.push_back(Movement::DOWN);

    if(mov.dirs.size() > 0)
        owner_->shape_component()->Move(mov);
        */
}

} // namespace component
} // namespace game