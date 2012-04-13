#ifndef BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_
#define BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_

// Inheritance
#include "game/components/graphic.h"

// External Dependencies
#include <list>                         // template class
#include <ugdk/base/engine.h>           // needed in the TEXT_MANAGER() macro
#include <ugdk/graphic/drawable/text.h> // needed for GetText(-)
#include <ugdk/graphic/node.h>          // needed for set_drawable(-)
#include <ugdk/graphic/textmanager.h>   // needed for the TEXT_MANAGER() macro

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class GraphicRectangular : public Graphic {
  typedef Graphic super;
  public:
    GraphicRectangular(std::wstring visual_representation)
      : super() {
        node()->set_drawable(TEXT_MANAGER()->GetText(visual_representation));
    }
    ~GraphicRectangular() {};

    void Update(double dt);

	void NodeLogic(const std::list<game::base::GameTile*>& occupying_tiles);
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_