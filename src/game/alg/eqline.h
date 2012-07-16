#ifndef BADGAME_ALG_EQLINE_H_
#define BADGAME_ALG_EQLINE_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/vector2D.h> // origin
#include <limits> // infinity()

// Internal Dependencies
#include "utils/utils.h"

// Forward Declarations
#include <ugdk/math.h>
using namespace utils::enums;

namespace game {
namespace alg {
    
class EqLine {
  public:
    EqLine(const ugdk::Vector2D& origin, const ugdk::Vector2D& target)
      : origin_(origin) {
        if( utils::CompareDoubles(target.x,origin.x) == ord::EQ ) {
            if( utils::CompareDoubles(target.y,origin.y) == ord::EQ ) {
                coefficient_ = 0.0;
                is_vertical_ = false;
                target_coord_ = target.x;
            } else {
                coefficient_ = std::numeric_limits<double>::infinity();
                is_vertical_ = true;
                target_coord_ = target.y;
            }
        } else {
            coefficient_ = (target.y - origin.y)/(target.x - origin.x);
            is_vertical_ = false;
            target_coord_ = target.x;
        }
    }
    ~EqLine() {}

    // getters

          ugdk::Vector2D& origin()       { return origin_; }
    const ugdk::Vector2D& origin() const { return origin_; }

          ugdk::Vector2D  target()       {
        return is_vertical_
                 ? ugdk::Vector2D(origin_.x, target_coord_)
                 : ugdk::Vector2D(target_coord_, coefficient_*(target_coord_-origin_.x) - origin_.y);
    }
    const ugdk::Vector2D  target() const {
        return is_vertical_
                 ? ugdk::Vector2D(origin_.x, target_coord_)
                 : ugdk::Vector2D(target_coord_, coefficient_*(target_coord_-origin_.x) - origin_.y);
    }
    
          double coefficient()       { return coefficient_; }
    const double coefficient() const { return coefficient_; }

          bool is_vertical()       { return is_vertical_; }
    const bool is_vertical() const { return is_vertical_; }

    //TODO: funções p/ ângulo, etc...

    // setters

    void set_origin(const ugdk::Vector2D& new_origin) {
        ugdk::Vector2D target = this->target();

        if(utils::CompareDoubles(target.x,new_origin.x) == ord::EQ) {
            if(utils::CompareDoubles(target.y,new_origin.y) == ord::EQ) {
                origin_ = new_origin;
                return;
            }
            is_vertical_ = true;
            coefficient_ = std::numeric_limits<double>::infinity();
            origin_ = new_origin;
            return;
        }

        coefficient_ = ( coefficient_*(target.x - origin_.x) - (new_origin.y - origin_.y) ) / (target.x - new_origin.x);
        origin_ = new_origin;
    }

    void set_target(const ugdk::Vector2D& new_target) {
        
        if(utils::CompareDoubles(new_target.x,origin_.x) == ord::EQ) {
            if(utils::CompareDoubles(new_target.y,origin_.y) == ord::EQ) {
                is_vertical_ ? target_coord_ = origin_.y : target_coord_ = origin_.x;
                return;
            }
            is_vertical_ = true;
            coefficient_ = std::numeric_limits<double>::infinity();
            target_coord_ = new_target.y;
            return;
        }

        coefficient_ = (new_target.y - origin_.y) / (new_target.x - origin_.x);
        target_coord_ = new_target.x;
    }
    //TODO: mais setters

    // métodos

    ord::Ord CompareWithVector(const ugdk::Vector2D& vec) {
        return utils::CompareDoubles(coefficient_*(vec.x - target().x) + target().y, vec.y);
    }

    static void Test() {
        int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0;

        EqLine line = EqLine(ugdk::Vector2D(0,0),ugdk::Vector2D(1,0));
        test1 = line.CompareWithVector(ugdk::Vector2D(2,0));
        printf("%d,%d,%d,%d,%d",test1,test2,test3,test4,test5);
        printf("\n");
    }

  private:
    ugdk::Vector2D origin_;
    double coefficient_;
    double target_coord_;
    bool is_vertical_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQLINE_H_