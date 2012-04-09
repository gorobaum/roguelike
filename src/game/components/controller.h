#ifndef TOPDOWN_GAME_COMPONENT_CONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_CONTROLLER_H_

#include <ugdk/graphic.h>

namespace game {

class GameTile;
class GameObject;

namespace component {

class Controller {
  public:
    Controller() : owner_(nullptr) {}
    ~Controller() {}

    void set_owner(GameObject* owner) { owner_ = owner; } 

    virtual void Update(double dt, game::GameObject* owner) = 0;

    virtual GameTile* PlaceAt(game::GameTile* tile) = 0;

  protected:
    GameObject* owner_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_CONTROLLER_H_