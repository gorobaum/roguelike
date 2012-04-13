#ifndef BADGAME_COMPONENT_DAMAGEABLE_H_
#define BADGAME_COMPONENT_DAMAGEABLE_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Damageable {
  public:
    Damageable(double max_life) : owner_(nullptr), current_life_(max_life), max_life_(max_life) {}
    ~Damageable() {}

    void set_owner(game::base::GameObject* owner) { owner_ = owner; } //TODO: Mudar para ser no construtor

    void Update(double dt);

    void Damage(double damage) { current_life_ -= damage; }

    double current_life() const { return current_life_; }

  protected:
    game::base::GameObject* owner_;

  private:
    double current_life_;
    double max_life_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_DAMAGEABLE_H_