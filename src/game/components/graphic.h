#ifndef BADGAME_COMPONENT_GRAPHIC_H_
#define BADGAME_COMPONENT_GRAPHIC_H_

#include <list>

#include <ugdk/graphic.h>

#include "game/gametile.h"

namespace game {

class GameObject;

namespace component {

class Graphic {
  public:
    Graphic();
    ~Graphic();

    void set_owner(const GameObject* owner) { owner_ = owner; } 

    virtual void Update(double dt) = 0;

	virtual void NodeLogic(const std::list<GameTile*>& occupying_tiles_) = 0;

          ugdk::graphic::Node* node()       { return node_; }
    const ugdk::graphic::Node* node() const { return node_; }

  protected:
    const GameObject* owner_;

  private:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_GRAPHIC_H_