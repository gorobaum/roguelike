#ifndef BADGAME_COMPONENT_SHAPE_H_
#define BADGAME_COMPONENT_SHAPE_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
#include <list> // template class

// Internal Dependencies
#include "game/action/movement.h"   // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Shape : public ComponentBase {
  typedef ComponentBase super;
  public:
    Shape(game::base::GameObject* owner, size_t size_class = 10)
      : super(owner), size_class_(size_class) {}
    ~Shape() {}

    void set_size_class(size_t size_class) { size_class = size_class_; }

    size_t size_class() const { return size_class_; }
    const std::list<game::base::GameTile*>& occupying_tiles() const { return occupying_tiles_; } 

    virtual game::base::GameTile* PlaceAt(game::base::GameTile* tile) = 0;
    virtual game::base::GameTile* Move(game::action::Movement& mov) = 0;
    virtual game::base::GameTile* Step(game::action::Movement::Direction dir) = 0;

  protected:
    size_t size_class_;
	std::list<game::base::GameTile*> occupying_tiles_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_H_