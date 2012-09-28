#ifndef ROGUELIKE_COMPONENT_VISION_H_
#define ROGUELIKE_COMPONENT_VISION_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <list> // eye_coords()
#include <set> // relevant_octants_
#include <ugdk/math/frame.h> // eye_frame_

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"
#include "game/alg.h"

namespace game {
namespace component {

class Vision : public ComponentBase {
  typedef ComponentBase super;
  public:
    Vision(game::base::GameObject* owner);
    virtual ~Vision();

    void Initialize(); //TODO: remove (see the TODOs on the alg::los namespace).

    const base::GameObject* owner() const { return owner_; }
    const ugdk::math::Integer2D& eye_coords() const {
        return owner_->shape_component()->occupying_tiles().front();
    }
    const ugdk::Frame& eye_frame() const { return eye_frame_; }
    double range() const { return range_; }
    const std::set<int>& relevant_octants() const { return relevant_octants_; }

    void MarkVisible(const ugdk::math::Integer2D& tile);
    bool BlocksVision(const ugdk::math::Integer2D& tile);

    void See();
    void CycleOctant();



  private:
    double range_;
    std::set<int> relevant_octants_;
    std::list<ugdk::math::Integer2D> visible_tiles_;
    alg::los::Processor* losprocessor_;

    ugdk::Frame eye_frame_;

    bool initialized_;
    game::base::GameController* gamecontroller_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_VISION_H_