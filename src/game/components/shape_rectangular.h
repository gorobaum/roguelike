#ifndef BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_
#define BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_

// Inheritance
#include "game/components/shape.h"

// External Dependencies
#include <set>
#include <vector>
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
#include "game/action/movement.h"   // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ShapeRectangular : public Shape {
  typedef Shape super;
  public:
    ShapeRectangular(game::base::GameObject* owner, size_t size_x = 1, size_t size_y = 1, double stay_sizeclass = 1.0, double pass_sizeclass = 0.25, double enter_sizeclass = 1.0e-5)
      : super(owner, stay_sizeclass, pass_sizeclass, enter_sizeclass),
        dimensions_(ugdk::Vector2D(size_x,size_y)),
        bumps_() {
        bumps_.resize(4);
    }
    ~ShapeRectangular() {}

    game::base::GameTile* PlaceAt(game::base::GameTile* destination);
    game::base::GameTile* Move(game::action::Movement& mov);
    game::base::GameTile* Step(game::action::Movement::Direction dir);

    bool CheckForOob(game::base::GameTile* destination);
    bool TryPlace(game::base::GameTile* destination);
    game::action::Movement::Direction TryStep(game::action::Movement::Direction dir);
    void EvalBumpsAt(game::base::GameTile* destination);

    const ugdk::Vector2D& dimensions() const { return dimensions_; }

  private:
    ugdk::Vector2D dimensions_;
    std::vector<const std::set<game::base::GameObject*>> bumps_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_