#include <ugdk/graphic/node.h>

#include "game/components/graphic.h"

#include "game/gameobject.h"

namespace game {
namespace component {

Graphic::Graphic() : node_(new ugdk::graphic::Node), owner_(nullptr) {}

Graphic::~Graphic() {
    delete node_;
}

void Graphic::Update(double dt) {
}

} // namespace component
} // namespace game