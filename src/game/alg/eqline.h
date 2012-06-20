#ifndef BADGAME_ALG_EQLINE_H_
#define BADGAME_ALG_EQLINE_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "utils/utils.h"

namespace game {
namespace alg {
    
class EqLine {
  public:
    EqLine(ugdk::Vector2D origin, ugdk::Vector2D target)
      : origin_(origin), target_x_(target.x) {
          if(utils::Utils::CompareDoubles((origin-target).LengthSquared(),0.0) == 0) {
              coefficient_ = 0.0;
              is_vertical_ = false;
          } else {
              coefficient_ = (target.x - origin.x)/(target.y - origin.y);
              is_vertical_ = utils::Utils::CompareDoubles(target.x,origin.x) == 0 ? true : false;
          }
    }
    ~EqLine() {}

    // getters

          ugdk::Vector2D origin()       { return origin_; }
    const ugdk::Vector2D origin() const { return origin_; }
    //TODO: gamb pro target.
          ugdk::Vector2D target()       { return ugdk::Vector2D(target_x_, coefficient_*(target_x_-origin_.x) - origin_.y); }
    const ugdk::Vector2D target() const { return ugdk::Vector2D(target_x_, coefficient_*(target_x_-origin_.x) - origin_.y); }
    
          double coefficient()       { return coefficient_; }
    const double coefficient() const { return coefficient_; }

          bool is_vertical()       { return is_vertical_; }
    const bool is_vertical() const { return is_vertical_; }

    //TODO: funções p/ ângulo, etc...

    // setters

    void set_origin(const ugdk::Vector2D& new_origin) {
        if( utils::Utils::CompareDoubles(target_x_ - new_origin.x, 0.0) == 0 ) {
            if( utils::Utils::CompareDoubles(target().y - new_origin.y, 0.0) == 0 ) {
                origin_ = new_origin;
                return;
            }
            is_vertical_ = true;
            //TODO: coef = +inf;
            return;
        }
        coefficient_ = ( coefficient_*(target_x_ - origin_.x) - (new_origin.y - origin_.y) ) / (target_x_ - new_origin.x);
        origin_ = new_origin;
    }
    void set_target(const ugdk::Vector2D& new_target) {
        if( utils::Utils::CompareDoubles(origin_.x - new_target.x, 0.0) == 0 ) {
            if( utils::Utils::CompareDoubles((origin_-new_target).LengthSquared(), 0.0) != 0 ) {
                //seta target_x_.;
                return;
            }
            is_vertical_ = true;
            //TODO: target p/ linhas verticais;
            return;
        }
        coefficient_ = (new_target.y - origin_.y) / (new_target.x - origin_.x);
        target_x_ = new_target.x;
    }
    /*TODO:
    void set_coefficient(const double coefficient) { coefficient_ = coefficient; }
    void set_target_x(const double target_x) { target_x_ = target_x; }
    void set_is_vertical(const bool is_vertical) { is_vertical_ = is_vertical; }
    */

    // métodos

    int CompareWithVector(const ugdk::Vector2D& vec) {
        return utils::Utils::CompareDoubles( coefficient_*(vec.x - origin_.x) + origin_.y, vec.y);
    }

  private:
    ugdk::Vector2D origin_;
    double coefficient_;
    double target_x_;
    bool is_vertical_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQLINE_H_