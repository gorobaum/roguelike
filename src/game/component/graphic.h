#ifndef BADGAME_COMPONENT_GRAPHIC_H_
#define BADGAME_COMPONENT_GRAPHIC_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <list> // template class

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include "game/base.h"

namespace game {
namespace component {

class Graphic : public ComponentBase {
  typedef ComponentBase super;
  public:
    Graphic(game::base::GameObject* owner, std::string visual_representation, double zindex);
    ~Graphic();

    virtual void Update(double dt) = 0;

	virtual void NodeLogic(const std::list<game::base::GameTile*>& occupying_tiles_) = 0;

          ugdk::graphic::Node* node()       { return node_; }
    const ugdk::graphic::Node* node() const { return node_; }

  private:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_H_