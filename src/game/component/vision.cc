// Header File
#include "game/component/vision.h"

// External Dependencies
#include <list>
// (none)
#include <ugdk/graphic/node.h>  //TODO rem.
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

Vision::Vision(game::base::GameObject* owner) : super(owner), range_(29.5), initialized_(false) {}

Vision::~Vision() {
    if(initialized_)
        delete losprocessor_;
}

void Vision::Initialize() {
    if(initialized_) return;

    for(int i = 0; i < 8; ++i)
        relevant_octants_.insert(i);
    
    losprocessor_ = new Processor(this);
    
    initialized_ = true;
    See();
}

void Vision::MarkVisible(const GameTile* tile) {
    tile->node()->modifier()->set_visible(true);
    //TODO: use visible_tiles_
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

    int i = (*rt) + 1;
    if(i == 8) i = 0;
    relevant_octants_.clear();
    relevant_octants_.insert(i);
    See();
}

bool Vision::BlocksVision(const GameTile* tile) {
    //TODO: POARR NAO TUDO BLOCA VISAO NEH
    const list<GameObject*> stuff = tile->objects_here();
    for(auto ot = stuff.begin(); ot != stuff.end(); ++ot) {
        if(*ot != owner_) return true;
    }
    return false;
}

} // namespace component
} // namespace game