#ifndef BADGAME_BUILDER_OBJECTBUILDER_H_
#define BADGAME_BUILDER_OBJECTBUILDER_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace builder {

class ObjectBuilder {
  public:
    ObjectBuilder();
    ~ObjectBuilder() {}

    game::base::GameObject* BuildHero();
    game::base::GameObject* BuildEnemy();
    game::base::GameObject* BuildItem();
};

} // namespace builder
} // namespace game

#endif // BADGAME_BUILDER_OBJECTBUILDER_H_