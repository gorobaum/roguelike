#ifndef BADGAME_COMPONENT_VISION_H_
#define BADGAME_COMPONENT_VISION_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
#include <list> // eye()
#include <set> // relevant_octants_

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/components/shape.h"

// Forward Declarations
#include "game/base.h"
#include "game/alg.h"

namespace game {
namespace component {

class Vision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Vision(game::base::GameObject* owner);
    ~Vision();

    const base::GameObject* owner() const { return owner_; }
    base::GameTile* eye() const { return owner_->shape_component()->occupying_tiles().front(); }
    double range() const { return range_; }
    const std::set<int>& relevant_octants() const { return relevant_octants_; }

    void MarkVisible(const base::GameTile* tile);

    void Update(double dt);

    bool BlocksVision(const base::GameTile* tile);

  private:
    // returns n_th octant's o'clock notation.
    int nth_orientation(int n) { return n + (n-1)/2; }

    double range_;
    std::set<int> relevant_octants_;
    std::list<base::GameTile*> visible_tiles_;
    alg::LosProcessor* losprocessor_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_VISION_H_