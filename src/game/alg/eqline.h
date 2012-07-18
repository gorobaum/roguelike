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
      : origin_(origin), target_x_(target.x) {
        if( utils::CompareDoubles(target.x,origin.x) == ord::EQ ) {
            // if both origin and target have the same x, the line is invalid.
#ifdef DEBUG
            fprintf(stderr,"BAD BAD PROGRAMMER: Invalid EqLine parameters at constructor:\n");
            fprintf(stderr,"  origin == (%f,%f)\n",origin.x,origin.y);
            fprintf(stderr,"  target == (%f,%f)\n",target.x,target.y);
#endif
        } else {
            coefficient_ = (target.y - origin.y)/(target.x - origin.x);
        }
    }
    ~EqLine() {}

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
    void set_origin(const ugdk::Vector2D& new_origin) {
        ugdk::Vector2D target = this->target();
        ugdk::Vector2D prevent_vert(0.0);

        if(utils::CompareDoubles(target.x,new_origin.x) == ord::EQ) {
            if(utils::CompareDoubles(target.y,new_origin.y) == ord::EQ) {
                origin_ = new_origin;
                return;
            }
#ifdef DEBUG
            fprintf(stderr,"EqLine soft Warning: Attempt of vertical line at set_origin:\n");
            fprintf(stderr,"  new_origin == (%f,%f)\n",new_origin.x,new_origin.y);
            fprintf(stderr,"  target == (%f,%f)\n",target.x,target.y);
#endif
            if(coefficient_ < 0) {
                if(utils::CompareDoubles(target.y,new_origin.y) == ord::LT) prevent_vert.x -= 0.0001;
                else prevent_vert.x += 0.0001;
            } else {
                if(utils::CompareDoubles(target.y,new_origin.y) == ord::LT) prevent_vert.x += 0.0001;
                else prevent_vert.x -= 0.0001;
            }
        }
        coefficient_ = ( coefficient_*(target.x - origin_.x) - (new_origin.y - origin_.y) ) / (target.x - (new_origin.x + prevent_vert.x));
        origin_ = new_origin + prevent_vert;
    }

    void set_target(const ugdk::Vector2D& new_target) {
        double prevent_vert = 0.0;
        
        if(utils::CompareDoubles(new_target.x,origin_.x) == ord::EQ) {
            if(utils::CompareDoubles(new_target.y,origin_.y) == ord::EQ) {
                target_x_ = origin_.x;
                return;
            }
#ifdef DEBUG
            fprintf(stderr,"EqLine soft Warning: Attempt of vertical line at set_target:\n");
            fprintf(stderr,"  origin_ == (%f,%f)\n",origin_.x,origin_.y);
            fprintf(stderr,"  new_target == (%f,%f)\n",new_target.x,new_target.y);
#endif
            if(coefficient_ < 0) {
                if(utils::CompareDoubles(new_target.y,origin_.y) == ord::LT) prevent_vert += 0.0001;
                else prevent_vert -= 0.0001;
            } else {
                if(utils::CompareDoubles(new_target.y,origin_.y) == ord::LT) prevent_vert -= 0.0001;
                else prevent_vert += 0.0001;
            }
        }
        coefficient_ = (new_target.y - origin_.y) / (new_target.x + prevent_vert - origin_.x);
        target_x_ = new_target.x + prevent_vert;
    }
    //TODO: mais setters

    // métodos
    double YAt(double x) const {
        double b = origin_.y + -coefficient_*origin_.x;
        return coefficient_*x + b;
    }

    ord::Ord CompareWithVector(const ugdk::Vector2D& vec) {
        // checks whether i.e. the line is above the point.
        return utils::CompareDoubles(YAt(vec.x), vec.y);
    }

#ifdef DEBUG
    static void Test() {
        int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0;

        EqLine line = EqLine(ugdk::Vector2D(0.0,0.0),ugdk::Vector2D(1.0,0.0));
        test1 = line.CompareWithVector(ugdk::Vector2D(2.0,0.0));

        line = EqLine(ugdk::Vector2D(0.0,0.0),ugdk::Vector2D(1.0,1.0));
        test2 = line.CompareWithVector(ugdk::Vector2D(2.0,0.0));
        
        line = EqLine(ugdk::Vector2D(-2.0,7.0),ugdk::Vector2D(22.0,1.0));
        test3 = line.CompareWithVector(ugdk::Vector2D(70.0,50.0));
        
        line = EqLine(ugdk::Vector2D(0.0,-10.0),ugdk::Vector2D(1.0,10.0));
        test4 = line.CompareWithVector(ugdk::Vector2D(-2.0,0.0));
        
        line = EqLine(ugdk::Vector2D(0.0,-10.0),ugdk::Vector2D(-1.0,10.0));
        test5 = line.CompareWithVector(ugdk::Vector2D(-2.0,0.0));

        printf("EqLine testes: %d,%d,%d,%d,%d",test1,test2,test3,test4,test5);
        printf("\n");
    }
#endif

  private:
    ugdk::Vector2D origin_;
    double coefficient_;
    double target_x_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQLINE_H_