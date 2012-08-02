
// Header File
#include "game/alg/equationalline.h"

// External Dependencies
#include <assert.h>
#include <limits>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "utils/utils.h"

// Using
using std::numeric_limits;
using ugdk::Vector2D;
using utils::CompareDoubles;
using namespace utils::enums;

// Defines
#ifndef DEBUG
    #define IS_EAGER(var) (!lazy_##var##_)
    #define IS_EAGER_VEC(vec) (IS_EAGER(vec##_x) && IS_EAGER(vec##_y))

    #define REQUIRE_EAGER(var) do {             \
            if(lazy_##var##_) update_##var##(); \
        } while(false)

    #define REQUIRE_EAGER_VEC(vec) REQUIRE_EAGER(vec##_x);  \
                                   REQUIRE_EAGER(vec##_y)
#else
    #define IS_EAGER(var) (!lazy_##var##_)
    #define IS_EAGER_VEC(vec) (IS_EAGER(vec##_x) && IS_EAGER(vec##_y))

    #define ASSERT_CONSISTENT() assert(                                                                                 \
            (!lazy_a_ && (!lazy_b_ || !lazy_origin_) ) ||                                                               \
            (!lazy_b_ && (!lazy_offset_target_ || (IS_EAGER_VEC(origin) && (origin_.x != 0.0 || origin_.y != b_)))) ||  \
            (IS_EAGER_VEC(origin) && IS_EAGER_VEC(offset_target))                                                       \
        ); (void) 0

    #define REQUIRE_EAGER(var) do {             \
            ASSERT_CONSISTENT();                \
            if(lazy_##var##_) update_##var##(); \
        } while(false)

    #define REQUIRE_EAGER_VEC(vec) REQUIRE_EAGER(vec##_x); \
                                   REQUIRE_EAGER(vec##_y)
#endif



namespace game {
namespace alg {

class EquationalLineImpl {
  public:
    // constructors and destructors
    EquationalLineImpl(double a, double b, bool use_left_as_up)
      : a_(a), b_(b), use_left_as_up_(use_left_as_up),
        lazy_a_(false), lazy_b_(false),
        lazy_origin_x_(true), lazy_origin_y_(true),
        lazy_offset_target_x_(true), lazy_offset_target_y_(true) {}

    EquationalLineImpl(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
      : use_left_as_up_(use_left_as_up), origin_(origin), offset_target_(target-origin),
        lazy_a_(true), lazy_b_(true),
        lazy_origin_x_(false), lazy_origin_y_(false),
        lazy_offset_target_x_(false), lazy_offset_target_y_(false) {}

    ~EquationalLineImpl() {}

    // getters
    double a() { /*REQUIRE_EAGER(a);*/ return a_; } 
    double b() { /*REQUIRE_EAGER(b);*/ return b_; }
    bool use_left_as_up() const { return use_left_as_up_; }

    const Vector2D& origin() {
        /*REQUIRE_EAGER_VEC(origin);*/
        return origin_;
    }
    const Vector2D& offset_target() {
        /*REQUIRE_EAGER_VEC(offset_target);*/
        return offset_target_;
    }

    // setters
    void set_a_keep_b_(double a) {
        REQUIRE_EAGER(b);
        a_ = a;
        lazy_origin_x_ = lazy_origin_y_ =
        lazy_offset_target_x_ = lazy_offset_target_y_ = true;
    }
    void set_a_keep_origin_(double a) {
        /*REQUIRE_EAGER_VEC(origin);*/
        a_ = a;
        lazy_b_ = true;
        lazy_offset_target_x_ = lazy_offset_target_y_ = true;
    }
    void set_b(double b) {
        b_ = b;
        origin_.y += b;
    }
    void set_use_left_as_up_(bool use_left_as_up) {
        use_left_as_up_ = use_left_as_up;
    }
    void set_origin(const Vector2D& origin) {
        /*REQUIRE_EAGER_VEC(offset_target);*/
        origin_ = origin;
        lazy_a_ = lazy_b_ = true;
    }
    void set_offset_target(const Vector2D& offset_target) {
        /*REQUIRE_EAGER_VEC(origin);*/
        offset_target_ = offset_target;
        lazy_a_ = lazy_b_ = true;
    }
    void set_target(const Vector2D& target) {
        /*REQUIRE_EAGER_VEC(origin);*/
        set_offset_target(origin_ - target);
    }

    // methods
    Vector2D Target() {
        /*REQUIRE_EAGER_VEC(origin); REQUIRE_EAGER_VEC(offset_target);*/
        return offset_target_ - origin_;
    }
    double YAt(double x) {
        /*REQUIRE_EAGER(a); REQUIRE_EAGER(b);*/
        return a_*x + b_;
    }
    utils::enums::ord::Ord CompareWithVector(const Vector2D& vec) {
        return utils::CompareDoubles(YAt(vec.x), vec.y);
    }

  private:
    // utility functions for lazyness
    void update_a() {
        // if the direction vector is stable, it's easy to calculate:
        if(IS_EAGER_VEC(offset_target)) {
            if( CompareDoubles(lazy_offset_target_x_,0.0) == ord::EQ ) {
                a_ = numeric_limits<double>::infinity();
            } else {
                a_ = offset_target_.y / offset_target_.x;
            }
        } else if(IS_EAGER(b)) {
            // então IS_EAGER(
        }


        lazy_a_ = false;
    }
    void update_b() {
        /*REQUIRE_EAGER(a); REQUIRE_EAGER_VEC(origin);*/

    }
    void update_origin_x() {}
    void update_origin_y() {}
    void update_offset_target_x() {}
    void update_offset_target_y() {}

    // attributes
    double a_;
    double b_;
    bool use_left_as_up_;
    Vector2D origin_;
    Vector2D offset_target_; // origin_ + offset_target_ == target()

    // lazyness attributes
    bool lazy_a_;
    bool lazy_b_;
    bool lazy_origin_x_;
    bool lazy_origin_y_;
    bool lazy_offset_target_x_;
    bool lazy_offset_target_y_;
};


// contructors and destructors
EquationalLine::EquationalLine(double a, double b, bool use_left_as_up)
  : pimpl_(new EquationalLineImpl(a,b,use_left_as_up)) {}

EquationalLine::EquationalLine(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
  : pimpl_(new EquationalLineImpl(origin,target,use_left_as_up)) {}

EquationalLine::~EquationalLine() { delete pimpl_; }

// getters
double EquationalLine::a() const {}
double EquationalLine::b() const {}
bool EquationalLine::use_left_as_up() const {}

const Vector2D& EquationalLine::origin() const {}
const Vector2D& EquationalLine::offset_target() const {}

// setters
void EquationalLine::set_a(double a) {}
void EquationalLine::set_b(double b) {}
void EquationalLine::set_origin(const Vector2D& new_origin) {}
void EquationalLine::set_target(const Vector2D& new_target) {}

// methods
Vector2D EquationalLine::Target() const {}
double EquationalLine::YAt(double x) const {}

ord::Ord EquationalLine::CompareWithVector(const Vector2D& vec) {}




} // namespace alg
} // namespace game