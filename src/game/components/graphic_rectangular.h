#ifndef BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_
#define BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_

#include <ugdk/base/engine.h>
#include <ugdk/graphic/textmanager.h>
#include <ugdk/graphic/drawable/text.h>

#include <list>

#include "game/components/graphic.h"

class ugdk::Vector2D;

namespace game {
namespace component {

class GraphicRectangular : public Graphic {
  typedef game::component::Graphic super;

  public:
    GraphicRectangular(std::wstring visual_representation)
      : game::component::Graphic() {
        node()->set_drawable(TEXT_MANAGER()->GetText(visual_representation));
    }
    ~GraphicRectangular() {};

    void Update(double dt);

	void NodeLogic(const std::list<GameTile*>& occupying_tiles_);

  private:
    ugdk::graphic::Drawable* drawable_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_RECTANGULAR_H_