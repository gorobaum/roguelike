#ifndef BADGAME_BUILDER_OBJECTBUILDER_H_
#define BADGAME_BUILDER_OBJECTBUILDER_H_

#include <ugdk/math/vector2D.h>
#include "game.h"

namespace game {
namespace builder {

class ObjectBuilder {
  public:
    ObjectBuilder();
    ~ObjectBuilder() {}

    GameObject* BuildHero();
    GameObject* BuildEnemy();
    GameObject* BuildItem();
};

} // namespace builder
} // namespace game

#endif // BADGAME_BUILDER_OBJECTBUILDER_H_