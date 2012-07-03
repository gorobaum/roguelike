// Header File
#include "game/components/vision.h"

// External Dependencies
#include <list>
// (none)
#include <ugdk/graphic/node.h>  //TODO rem.
#include <ugdk/graphic/modifier.h> //TODO rem.

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/alg/losprocessor.h"

// Using
using std::list;
using game::base::GameObject;
using game::base::GameTile;
using game::alg::LosProcessor;

namespace game {
namespace component {

Vision::Vision(game::base::GameObject* owner) : super(owner), range_(10.0) {
    for(int i = 1; i <= 8; ++i)
        relevant_octants_.insert(nth_orientation(i));

    losprocessor_ = new LosProcessor(this);
}

Vision::~Vision() {
    delete losprocessor_;
}

void Vision::MarkVisible(const GameTile* tile) {
    tile->node()->modifier()->set_visible(true);
    //TODO use visible_tiles_
}

void Vision::Update(double) {
    losprocessor_->Process();
}

bool Vision::BlocksVision(const GameTile* tile) {
    const list<GameObject*> stuff = tile->objects_here();
    for(auto ot = stuff.begin(); ot != stuff.end(); ++ot) {
        if(*ot != owner_ ) return true;
    }
    return false;
}

} // namespace component
} // namespace game