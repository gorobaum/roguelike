#ifndef BADGAME_COMPONENT_VISION_H_
#define BADGAME_COMPONENT_VISION_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <list> // eye()
#include <set> // relevant_octants_

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h" //TODO: remove
#include "game/component/shape.h"

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

    void Initialize();

    const base::GameObject* owner() const { return owner_; }
    //TODO: transform into return const.
    ugdk::math::Integer2D eye() const {
        base::GameTile* tile = owner_->shape_component()->occupying_tiles().front();
        return ugdk::math::Integer2D(tile->x(),tile->y());
    }
    double range() const { return range_; }
    const std::set<int>& relevant_octants() const { return relevant_octants_; }

    void MarkVisible(const base::GameTile* tile);

    void Update(double);
    void See();

    void CycleOctant();

    bool BlocksVision(const base::GameTile* tile);

  private:
    double range_;
    std::set<int> relevant_octants_;
    std::list<base::GameTile*> visible_tiles_;
    alg::los::Processor* losprocessor_;

    bool initialized_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_VISION_H_