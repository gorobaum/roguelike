#ifndef BADGAME_ALG_EQLINE_H_
#define BADGAME_ALG_EQLINE_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/vector2D.h> // origin_

// Internal Dependencies
#include "utils/utils.h"

// Forward Declarations
// (none)

namespace game {
namespace alg {
    
class EqLine {
  public:
    EqLine(const ugdk::Vector2D& origin, const ugdk::Vector2D& target);
    ~EqLine();

    // getters
          ugdk::Vector2D& origin()       { return origin_; }
    const ugdk::Vector2D& origin() const { return origin_; }

          ugdk::Vector2D  target()       {
        return ugdk::Vector2D(target_x_, coefficient_*(target_x_-origin_.x) - origin_.y);
    }
    const ugdk::Vector2D  target() const {
        return ugdk::Vector2D(target_x_, coefficient_*(target_x_-origin_.x) - origin_.y);
    }
    
          double coefficient()       { return coefficient_; }
    const double coefficient() const { return coefficient_; }

    //TODO: funções p/ ângulo, etc...

    // setters
    void set_origin(const ugdk::Vector2D& new_origin);
    void set_target(const ugdk::Vector2D& new_target);
    //TODO: mais setters

    // métodos
    double YAt(double x) const {
        double b = origin_.y + -coefficient_*origin_.x;
        return coefficient_*x + b;
    }

    utils::enums::ord::Ord CompareWithVector(const ugdk::Vector2D& vec) {
        // checks whether i.e. the line is above the point.
        return utils::CompareDoubles(YAt(vec.x), vec.y);
    }

#ifdef DEBUG
    static void Test();
#endif

  private:
    ugdk::Vector2D origin_;
    double coefficient_;
    double target_x_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQLINE_H_