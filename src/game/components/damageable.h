#ifndef BADGAME_COMPONENT_DAMAGEABLE_H_
#define BADGAME_COMPONENT_DAMAGEABLE_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Damageable : public ComponentBase {
  typedef ComponentBase super;
  public:
    Damageable(game::base::GameObject* owner, double max_life)
        : super(owner), current_life_(max_life), max_life_(max_life) {}
    ~Damageable() {}

    void Update(double dt);

    void Damage(double damage) { current_life_ -= damage; }

    double current_life() const { return current_life_; }

  private:
    double current_life_;
    double max_life_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_DAMAGEABLE_H_