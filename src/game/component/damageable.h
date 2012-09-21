#ifndef ROGUELIKE_COMPONENT_DAMAGEABLE_H_
#define ROGUELIKE_COMPONENT_DAMAGEABLE_H_

// Inheritance
#include "game/component/componentbase.h"

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

    void TakeDamage(double damage);
    void StartToDie();

    double current_life() const { return current_life_; }

  private:
    double current_life_;
    double max_life_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_DAMAGEABLE_H_