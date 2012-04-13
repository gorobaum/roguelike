// Header File
#include "game/components/controller_player.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/builders/objectbuilder.h"
#include "game/components/shape.h"

// Using
using ugdk::input::InputManager;
using game::base::GameObject;
using game::action::Movement;

namespace game {
namespace component {

void ControllerPlayer::Update(double dt) {
    InputManager* input = INPUT_MANAGER();

	Movement mov;

    if(input->KeyPressed(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_d))
		mov.dirs.push_back(Movement::RIGHT);
	else if(input->KeyPressed(ugdk::input::K_LEFT) || input->KeyDown(ugdk::input::K_a))
		mov.dirs.push_back(Movement::LEFT);
    else if(input->KeyPressed(ugdk::input::K_UP)   || input->KeyDown(ugdk::input::K_w))
		mov.dirs.push_back(Movement::UP);
    else if(input->KeyPressed(ugdk::input::K_DOWN) || input->KeyDown(ugdk::input::K_s))
		mov.dirs.push_back(Movement::DOWN);

    if(mov.dirs.size() > 0)
        owner_->shape_component()->Move(mov);
}

} // namespace component
} // namespace game