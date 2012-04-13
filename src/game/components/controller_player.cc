// Header File
#include "game/components/controller_player.h"

// External Dependencies
#include <ugdk/base/engine.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time/timeaccumulator.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/builders/objectbuilder.h"

// Using
using ugdk::input::InputManager;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using game::action::Movement;

namespace game {
namespace component {

void ControllerPlayer::Update(double dt, GameObject* owner) {
    InputManager* input = INPUT_MANAGER();

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

    //TODO: Fix
    /*
	if(mov.dirs.size() > 0)
        next_tile = GameController::reference_->GetTileByMovementFromTile(owner_->occupying_tiles().front(), mov);

	if(next_tile)
		PlaceAt(next_tile);*/

}

} // namespace component
} // namespace game