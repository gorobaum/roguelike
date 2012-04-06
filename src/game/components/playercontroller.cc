#include <ugdk/base/engine.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>
#include <ugdk/time/timeaccumulator.h>

#include "game/components/playercontroller.h"

#include "game/gameobject.h"
#include "game/gamecontroller.h"
#include "game/builders/objectbuilder.h"

namespace game {
namespace component {

PlayerController::PlayerController() {}
PlayerController::~PlayerController() {}

void PlayerController::Update(double dt, GameObject* owner) {
    ugdk::input::InputManager* input = INPUT_MANAGER();

	GameTile* next_tile = nullptr;
	Movement mov;

    if(input->KeyPressed(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_d))
		mov.dirs.push_back(Movement::RIGHT);
	else if(input->KeyPressed(ugdk::input::K_LEFT) || input->KeyDown(ugdk::input::K_a))
		mov.dirs.push_back(Movement::LEFT);
    else if(input->KeyPressed(ugdk::input::K_UP)   || input->KeyDown(ugdk::input::K_w))
		mov.dirs.push_back(Movement::UP);
    else if(input->KeyPressed(ugdk::input::K_DOWN) || input->KeyDown(ugdk::input::K_s))
		mov.dirs.push_back(Movement::DOWN);
	/*
	if(mov.dirs.size() > 0)
		next_tile = game::GameController::reference_->GetTileByMovementFromTile(owner->game_tile(), mov);

	if(next_tile)
		owner->MoveTo(next_tile);
	*/

}

} // namespace component
} // namespace game