
// Header File
#include "game/alg/equationallinedouble.h"

// External Dependencies
#include <assert.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "utils/utils.h"

// Using
using ugdk::Vector2D;
using utils::CompareDoubles;
using namespace utils::enums;
using utils::enums::ord::Ord;

namespace game {
namespace alg {

class EquationalLineDoubleImpl {
  public:
    // constructors and destructors
    EquationalLineDoubleImpl(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
      : use_left_as_up_(use_left_as_up), origin_(origin), target_(target),
        lazy_a_(true), lazy_b_(true) {}

    ~EquationalLineDoubleImpl() {}

    // getters
    double a() { if(lazy_a_) update_a(); return a_; } 
    double b() { if(lazy_b_) update_b(); return b_; }
    bool use_left_as_up() const { return use_left_as_up_; }

    const Vector2D& origin() const { return origin_; }
    const Vector2D& target() const { return target_; }

    // setters
    void set_origin(const Vector2D& origin) {
        assert(origin.x != target_.x || origin.y != target_.y);
        origin_ = origin;
        lazy_a_ = lazy_b_ = true;
    }
    void set_target(const Vector2D& target) {
        assert(origin_.x != target.x || origin_.y != target.y);
        target_ = target;
        lazy_a_ = lazy_b_ = true;
    }
    void set_use_left_as_up(bool use_left_as_up) { use_left_as_up_ = use_left_as_up; }

    // methods
    double YAt(double x) {
        if(lazy_b_) update_b(); // requires fresh a_ already
        assert(!is_vertical_);

        return a_*x + b_;
    }
    Ord CompareWith(const Vector2D& vec) {
        if(lazy_a_) update_a();

        if(is_vertical_) {
            if(use_left_as_up_)
                return CompareDoubles(origin_.x, vec.x);
            return CompareDoubles(vec.x, origin_.x);
        }

        return CompareDoubles(YAt(vec.x), vec.y);
    }

  private:
    // utility functions for lazyness
    void update_a() {
        if(CompareDoubles(origin_.x,target_.x) == ord::EQ)
            is_vertical_ = true;
        else {
            a_ = (origin_.y - target_.y) / (origin_.x - target_.x);
            is_vertical_ = false;
        }

        lazy_a_ = false;
    }
    void update_b() {
        if(lazy_a_) update_a();

        if(!is_vertical_)
            b_ = origin_.y - a_ * origin_.x;

        lazy_b_ = false;
    }

    // attributes
    double a_;
    double b_;
    bool use_left_as_up_;
    Vector2D origin_;
    Vector2D target_;
    bool is_vertical_;

    // lazyness attributes
    bool lazy_a_;
    bool lazy_b_;
};

// contructors and destructors
EquationalLineDouble::EquationalLineDouble(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
  : pimpl_(new EquationalLineDoubleImpl(origin,target,use_left_as_up)) {}

EquationalLineDouble::EquationalLineDouble(const EquationalLineDouble& copy) : pimpl_(new EquationalLineDoubleImpl(*(copy.pimpl_))) {}

EquationalLineDouble::~EquationalLineDouble() { delete pimpl_; }

// getters
double EquationalLineDouble::a() const { return pimpl_->a(); }
double EquationalLineDouble::b() const { return pimpl_->b(); }
bool EquationalLineDouble::use_left_as_up() const { return pimpl_->use_left_as_up(); }
const Vector2D& EquationalLineDouble::origin() const { return pimpl_->origin(); }
const Vector2D& EquationalLineDouble::target() const { return pimpl_->target(); }

// setters
void EquationalLineDouble::set_origin(const Vector2D& origin) { pimpl_->set_origin(origin); }
void EquationalLineDouble::set_target(const Vector2D& target) { pimpl_->set_target(target); }

// methods
double EquationalLineDouble::YAt(double x) const { return pimpl_->YAt(x); }
Ord EquationalLineDouble::CompareWith(const Vector2D& vec) { return pimpl_->CompareWith(vec); }




} // namespace alg
} // namespace game