#ifndef BADGAME_COMPONENT_GRAPHIC_H_
#define BADGAME_COMPONENT_GRAPHIC_H_

#include <list>

#include <ugdk/graphic.h>

#include "game.h"
#include "game/gametile.h"

namespace game {
namespace component {

class Graphic {
  //typedef ugdk::Scene super;
  public:
    Graphic();
    ~Graphic();

    void Update(double dt, GameObject* owner);

	virtual void NodeLogic(std::list<GameTile*> occupying_tiles_) = 0;

          ugdk::graphic::Node* node()       { return node_; }
    const ugdk::graphic::Node* node() const { return node_; }

  private:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_H_