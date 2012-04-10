#include <ugdk/base/engine.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>
#include <ugdk/time/timeaccumulator.h>

#include "game/components/controller_player.h"

#include "game/gameobject.h"
#include "game/gamecontroller.h"
#include "game/gametile.h"
#include "game/builders/objectbuilder.h"

namespace game {
namespace component {

void ControllerPlayer::Update(double dt, GameObject* owner) {
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


	if(mov.dirs.size() > 0)
        next_tile = game::GameController::reference_->GetTileByMovementFromTile(owner_->occupying_tiles().front(), mov);

	if(next_tile)
		PlaceAt(next_tile);

}

GameTile* ControllerPlayer::PlaceAt(game::GameTile* destination) {
    
    for( auto xt = owner_->occupying_tiles().begin() ; xt != owner_->occupying_tiles().end() ; ++xt )
        (*xt)->RemoveObject(this->owner_);
    owner_->occupying_tiles().clear();

    GameController* gamecontroller = game::GameController::reference_;

    for( int i = 0 ; i < owner_->dimensions().x ; ++i ) {
        for( int j = 0 ; j < owner_->dimensions().y ; ++j ) {
            GameTile* tile = gamecontroller->GetTileFromCoordinates(destination->x()+i,destination->y()+j);
            owner_->occupying_tiles().push_back(tile);
            tile->PushObject(owner_);
        }
    }

    return destination; //TODO: make use of this. (implement PlaceAt(...) deflecting or failing).
}

} // namespace component
} // namespace game