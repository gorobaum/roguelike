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

namespace game {
namespace component {

class Vision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Vision(game::base::GameObject* owner) : super(owner), range_(10.0) {
        for(int i = 1; i <= 8; ++i)
            relevant_octants_.insert(nth_orientation(i));
    }
    ~Vision() {}

    const base::GameObject* owner() const { return owner_; }
    base::GameTile* eye() const { return owner_->shape_component()->occupying_tiles().front(); }
    double range() const { return range_; }
    const std::set<int>& relevant_octants() const { return relevant_octants_; }

    void MarkVisible(const base::GameTile* tile);

  private:
    int nth_orientation(int n) {
        switch(n) {
            case 8: case 7: return n+3;
            case 6: case 5: return n+2;
            case 4: case 3: return n+1;
            case 2: case 1: return n;
            default: return 0;
        }
    }

    double range_;
    std::set<int> relevant_octants_;
    std::list<GameTile*> visible_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_VISION_H_