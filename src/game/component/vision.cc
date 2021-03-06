// Header File
#include "game/component/vision.h"

// External Dependencies
#include <set>
#include <ugdk/math/frame.h>
#include <ugdk/math/integer2D.h>

#include <ugdk/graphic/node.h>     //TODO rem.
#include <ugdk/graphic/modifier.h> //TODO rem.

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/alg/los/processor.h"

// Using
using std::set;
using ugdk::math::Integer2D;
using game::base::GameController;
using game::base::GameObject;
using game::alg::los::Processor;

namespace game {
namespace component {

Vision::Vision(game::base::GameObject* owner)
  : super(owner), range_(20.5), eye_frame_(0.45, 0.10, 0.55, 0.20),
    initialized_(false), gamecontroller_(nullptr) {}

Vision::~Vision() {
    if(initialized_)
        delete losprocessor_;
}

void Vision::Initialize() {
    if(initialized_) return;

    gamecontroller_ = GameController::reference();
    for(int i = 0; i < 8; ++i)
        relevant_octants_.insert((i+0)%8);
    
    losprocessor_ = new Processor(this);
    
    initialized_ = true;
}

void Vision::MarkVisible(const Integer2D& tile) {
    //TODO: use visible_tiles_
    gamecontroller_->Tile(tile)->node()->modifier()->set_visible(true);
}

void Vision::See() {
    //TODO: use visible_tiles_
    gamecontroller_->BlackoutTiles();
    losprocessor_->Process();
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

bool Vision::BlocksVision(const Integer2D& tile) {
    //TODO: POARR NAO TUDO BLOCA VISAO NEH
    const set<GameObject*>& stuff = gamecontroller_->Tile(tile)->objects_here();
    for(auto ot = stuff.begin(); ot != stuff.end(); ++ot) {
        if(*ot != owner_) return true;
    }
    return false;
}

} // namespace component
} // namespace game