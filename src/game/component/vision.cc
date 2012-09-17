// Header File
#include "game/component/vision.h"

// External Dependencies
#include <list>

#include <ugdk/graphic/node.h>     //TODO rem.
#include <ugdk/graphic/modifier.h> //TODO rem.

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/alg/los/processor.h"

// Using
using std::list;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;
using game::alg::los::Processor;

namespace game {
namespace component {

Vision::Vision(game::base::GameObject* owner) : super(owner), range_(20.5), initialized_(false) {}

Vision::~Vision() {
    if(initialized_)
        delete losprocessor_;
}

void Vision::Initialize() {
    if(initialized_) return;

    for(int i = 0; i < 6; ++i)
        relevant_octants_.insert(i);
    
    losprocessor_ = new Processor(this);
    
    initialized_ = true;
    See();
}

void Vision::MarkVisible(const GameTile* tile) {
    //TODO: use visible_tiles_
	if( tile != nullptr ) 
		tile->node()->modifier()->set_visible(true);
}

void Vision::Update(double) {}

void Vision::See() {
    const GameController* gamecontroller = GameController::reference();

    gamecontroller->BlackoutTiles();
    losprocessor_->Process();
    //TODO: use visible_tiles_
}

void Vision::CycleOctant() {
	auto rt = relevant_octants_.begin();
	int i = *rt;
	while( (++rt != relevant_octants_.end()) && i+1 == *(rt) )
		++i;
	if( rt != relevant_octants_.end() )
		relevant_octants_.erase(*rt);
	else
		relevant_octants_.erase(*(relevant_octants_.begin()));
	
	relevant_octants_.insert((i+1)%8);
    See();
}

bool Vision::BlocksVision(const GameTile* tile) {
	if( tile == nullptr ) return true;
    //TODO: POARR NAO TUDO BLOCA VISAO NEH
    const list<GameObject*>& stuff = tile->objects_here();
    for(auto ot = stuff.begin(); ot != stuff.end(); ++ot) {
        if(*ot != owner_) return true;
    }
    return false;
}

} // namespace component
} // namespace game