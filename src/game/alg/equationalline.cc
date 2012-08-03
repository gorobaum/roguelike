
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

namespace game {
namespace alg {

class EquationalLineImpl {
  public:
    // constructors and destructors
    EquationalLineImpl(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
      : use_left_as_up_(use_left_as_up), origin_(origin), target_(target),
        lazy_a_(true), lazy_b_(true) {}

    ~EquationalLineImpl() {}

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
        assert(a_ != numeric_limits<double>::infinity());

        return a_*x + b_;
    }
    utils::enums::ord::Ord CompareWithVector(const Vector2D& vec) {
        if(lazy_a_) update_a();

        if(a_ == numeric_limits<double>::infinity()) {
            if(use_left_as_up_)
                return CompareDoubles(origin_.x,vec.x);

            return CompareDoubles(vec.x,origin_.x);
        }


        return CompareDoubles(YAt(vec.x), vec.y);
    }

  private:
    // utility functions for lazyness
    void update_a() {
        if(CompareDoubles(origin_.x,target_.x) == ord::EQ)
            a_ = numeric_limits<double>::infinity();
        else
            a_ = (origin_.y - target_.y) / (origin_.x - target_.x);

        lazy_a_ = false;
    }
    void update_b() {
        if(lazy_a_) update_a();

        if(a_ == numeric_limits<double>::infinity())
            b_ = -42.12345; // rofl. doesn't matter actually.
        else
            b_ = origin_.y - a_ * origin_.x;

        lazy_b_ = false;
    }

    // attributes
    double a_;
    double b_;
    bool use_left_as_up_;
    Vector2D origin_;
    Vector2D target_;

    // lazyness attributes
    bool lazy_a_;
    bool lazy_b_;
};

// contructors and destructors
EquationalLine::EquationalLine(const Vector2D& origin, const Vector2D& target, bool use_left_as_up)
  : pimpl_(new EquationalLineImpl(origin,target,use_left_as_up)) {}

EquationalLine::~EquationalLine() { delete pimpl_; }

// getters
double EquationalLine::a() const { return pimpl_->a(); }
double EquationalLine::b() const { return pimpl_->b(); }
bool EquationalLine::use_left_as_up() const { return pimpl_->use_left_as_up(); }
const Vector2D& EquationalLine::origin() const { return pimpl_->origin(); }
const Vector2D& EquationalLine::target() const { return pimpl_->target(); }

// setters
void EquationalLine::set_origin(const Vector2D& origin) { pimpl_->set_origin(origin); }
void EquationalLine::set_target(const Vector2D& target) { pimpl_->set_target(target); }

// methods
double EquationalLine::YAt(double x) const { return pimpl_->YAt(x); }
ord::Ord EquationalLine::CompareWithVector(const Vector2D& vec) { return pimpl_->CompareWithVector(vec); }




} // namespace alg
} // namespace game