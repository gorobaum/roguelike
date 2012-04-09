#ifndef BADGAME_COMPONENT_DAMAGEABLE_H_
#define BADGAME_COMPONENT_DAMAGEABLE_H_

#include <ugdk/graphic.h>

namespace game {

class GameObject;

namespace component {

class Damageable {
  public:
    Damageable(double max_life) : current_life_(max_life), max_life_(max_life) {}
    ~Damageable() {}

    void Update(double dt, GameObject* owner);

    void Damage(double damage) { current_life_ -= damage; }

    double current_life() const { return current_life_; }

  private:
    double current_life_;
    double max_life_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_DAMAGEABLE_H_