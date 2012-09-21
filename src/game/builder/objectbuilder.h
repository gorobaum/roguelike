#ifndef ROGUELIKE_BUILDER_OBJECTBUILDER_H_
#define ROGUELIKE_BUILDER_OBJECTBUILDER_H_

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
    ObjectBuilder() {}
    ~ObjectBuilder() {}

    game::base::GameObject* BuildHero();
    game::base::GameObject* BuildEnemy();
    game::base::GameObject* BuildItem();
    game::base::GameObject* BuildWall();
};

} // namespace builder
} // namespace game

#endif // ROGUELIKE_BUILDER_OBJECTBUILDER_H_