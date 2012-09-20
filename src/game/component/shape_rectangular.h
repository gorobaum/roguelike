#ifndef BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_
#define BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_

// Inheritance
#include "game/component/shape.h"

// External Dependencies
#include <set>
#include <vector>
#include <ugdk/math/integer2D.h> // needed for dimensions_

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ShapeRectangular : public Shape {
  typedef Shape super;
  public:
    ShapeRectangular(
        game::base::GameObject* owner, int size_x = 1, int size_y = 1,
        double stay_sizeclass = 1.0, double pass_sizeclass = 0.25, double enter_sizeclass = 1.0e-5
    );
    ~ShapeRectangular();

	const ugdk::math::Integer2D& PlaceAt(const ugdk::math::Integer2D& destination);
    const ugdk::math::Integer2D& Move(const std::list<ugdk::math::Integer2D>& mov);
    const ugdk::math::Integer2D& Step(const ugdk::math::Integer2D& dir);

    bool CheckForOob(const ugdk::math::Integer2D& destination);
    bool TryPlace(const ugdk::math::Integer2D& destination);
    ugdk::math::Integer2D TryStep(const ugdk::math::Integer2D& dir);

    void EvalBumpsAt(const ugdk::math::Integer2D& destination);

    const ugdk::math::Integer2D& dimensions() const { return dimensions_; }

  private:
    ugdk::math::Integer2D dimensions_;
    std::vector<const std::set<game::base::GameObject*>> bumps_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_