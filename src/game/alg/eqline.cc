
// Header File
#include "game/alg/eqline.h"

// External Dependencies
#include <cstdio>

// Internal Dependencies
#include "utils/utils.h"

// Using
using ugdk::Vector2D;
using namespace utils::enums;
using utils::CompareDoubles;

namespace game {
namespace alg {

EqLine::EqLine(const Vector2D& origin, const Vector2D& target)
  : origin_(origin), target_x_(target.x) {
    if( CompareDoubles(target.x,origin.x) == ord::EQ ) {
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
EqLine::~EqLine() {}

void EqLine::set_origin(const Vector2D& new_origin) {
    Vector2D target = this->target();
    Vector2D prevent_vert(0.0);

    if(CompareDoubles(target.x,new_origin.x) == ord::EQ) {
        if(CompareDoubles(target.y,new_origin.y) == ord::EQ) {
            origin_ = new_origin;
            return;
        }
#ifdef DEBUG
        fprintf(stderr,"EqLine soft Warning: Attempt of vertical line at set_origin:\n");
        fprintf(stderr,"  new_origin == (%f,%f)\n",new_origin.x,new_origin.y);
        fprintf(stderr,"  target == (%f,%f)\n",target.x,target.y);
#endif
        if(coefficient_ < 0) {
            if(CompareDoubles(target.y,new_origin.y) == ord::LT) prevent_vert.x -= 0.0001;
            else prevent_vert.x += 0.0001;
        } else {
            if(CompareDoubles(target.y,new_origin.y) == ord::LT) prevent_vert.x += 0.0001;
            else prevent_vert.x -= 0.0001;
        }
    }
    coefficient_ = ( coefficient_*(target.x - origin_.x) - (new_origin.y - origin_.y) ) / (target.x - (new_origin.x + prevent_vert.x));
    origin_ = new_origin + prevent_vert;
}


void EqLine::set_target(const Vector2D& new_target) {
    double prevent_vert = 0.0;
        
    if(CompareDoubles(new_target.x,origin_.x) == ord::EQ) {
        if(CompareDoubles(new_target.y,origin_.y) == ord::EQ) {
            target_x_ = origin_.x;
            return;
        }
#ifdef DEBUG
        fprintf(stderr,"EqLine soft Warning: Attempt of vertical line at set_target:\n");
        fprintf(stderr,"  origin_ == (%f,%f)\n",origin_.x,origin_.y);
        fprintf(stderr,"  new_target == (%f,%f)\n",new_target.x,new_target.y);
#endif
        if(coefficient_ < 0) {
            if(CompareDoubles(new_target.y,origin_.y) == ord::LT) prevent_vert += 0.0001;
            else prevent_vert -= 0.0001;
        } else {
            if(CompareDoubles(new_target.y,origin_.y) == ord::LT) prevent_vert -= 0.0001;
            else prevent_vert += 0.0001;
        }
    }
    coefficient_ = (new_target.y - origin_.y) / (new_target.x + prevent_vert - origin_.x);
    target_x_ = new_target.x + prevent_vert;

    // always try to move the origin, not the target.
    if(prevent_vert != 0.0) {
        set_origin(origin_ + Vector2D(-prevent_vert,0.0));
        set_target(new_target);
    }
}

void EqLine::Test() {
    int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0;

    EqLine line = EqLine(Vector2D(0.0,0.0),Vector2D(1.0,0.0));
    test1 = line.CompareWithVector(Vector2D(2.0,0.0));

    line = EqLine(Vector2D(0.0,0.0),Vector2D(1.0,1.0));
    test2 = line.CompareWithVector(Vector2D(2.0,0.0));
        
    line = EqLine(Vector2D(-2.0,7.0),Vector2D(22.0,1.0));
    test3 = line.CompareWithVector(Vector2D(70.0,50.0));
        
    line = EqLine(Vector2D(0.0,-10.0),Vector2D(1.0,10.0));
    test4 = line.CompareWithVector(Vector2D(-2.0,0.0));
        
    line = EqLine(Vector2D(0.0,-10.0),Vector2D(-1.0,10.0));
    test5 = line.CompareWithVector(Vector2D(-2.0,0.0));

    printf("EqLine testes: %d,%d,%d,%d,%d",test1,test2,test3,test4,test5);
    printf("\n");
}

} // namespace alg
} // namespace game