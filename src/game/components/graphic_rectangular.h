#ifndef BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_
#define BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_

// Inheritance
#include "game/components/graphic.h"

// External Dependencies
#include <list> // template class

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class GraphicRectangular : public Graphic {
  typedef Graphic super;
  public:
    GraphicRectangular(game::base::GameObject* owner, std::wstring visual_representation, double zindex);
    ~GraphicRectangular();

    void Update(double dt);

	void NodeLogic(const std::list<game::base::GameTile*>& occupying_tiles);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_