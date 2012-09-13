#ifndef BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_
#define BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_

// Inheritance
#include "game/component/shape.h"

// External Dependencies
#include <set>
#include <vector>
#include <ugdk/math/integer2D.h> // needed for dimensions_

// Internal Dependencies
#include "game/action/movement.h" // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ShapeRectangular : public Shape {
  typedef Shape super;
  public:
    ShapeRectangular(
        game::base::GameObject* owner,
        double size_x = 1, double size_y = 1,
        double stay_sizeclass = 1.0, double pass_sizeclass = 0.25, double enter_sizeclass = 1.0e-5
    );
    ~ShapeRectangular();

    game::base::GameTile* PlaceAt(game::base::GameTile* destination);
    game::base::GameTile* Move(game::action::Movement& mov);
    game::base::GameTile* Step(game::action::Movement::Direction dir);

    bool CheckForOob(game::base::GameTile* destination);
    bool TryPlace(game::base::GameTile* destination);
    game::action::Movement::Direction TryStep(game::action::Movement::Direction dir);
    void EvalBumpsAt(game::base::GameTile* destination);

    const ugdk::math::Integer2D& dimensions() const { return dimensions_; }

  private:
    ugdk::math::Integer2D dimensions_;
    std::vector<const std::set<game::base::GameObject*>> bumps_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_