
// Header File
#include "game/alg/equationalline.h"

// External Dependencies
#include <assert.h>
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "utils/utils.h"

// Using
using ugdk::math::Integer2D;
using utils::CompareDoubles;
using utils::CompareInts;
using namespace utils::enums;
using utils::enums::ord::Ord;

namespace game {
namespace alg {

class EquationalLineImpl {
  public:
    // constructors and destructors
    EquationalLineImpl(const Integer2D& origin, const Integer2D& target, bool use_left_as_up)
      : use_left_as_up_(use_left_as_up), origin_(origin), target_(target),
        lazy_a_(true), lazy_b_(true) {}

    ~EquationalLineImpl() {}

    // getters
    double a() { if(lazy_a_) update_a(); return a_; } 
    double b() { if(lazy_b_) update_b(); return b_; }
    bool use_left_as_up() const { return use_left_as_up_; }

    const Integer2D& origin() const { return origin_; }
    const Integer2D& target() const { return target_; }

    // setters
    void set_origin(const Integer2D& origin) {
        assert(origin.x != target_.x || origin.y != target_.y);
        origin_ = origin;
        lazy_a_ = lazy_b_ = true;
    }
    void set_target(const Integer2D& target) {
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
    Ord CompareWithInteger2D(const Integer2D& vec) {
        if(lazy_a_) update_a();

        if(is_vertical_) {
            if(use_left_as_up_)
                return CompareInts(origin_.x, vec.x);
            return CompareInts(vec.x, origin_.x);
        }

        return CompareDoubles(YAt(static_cast<double>(vec.x)), static_cast<double>(vec.y));
    }

  private:
    // utility functions for lazyness
    void update_a() {
        if(CompareInts(origin_.x,target_.x) == ord::EQ)
            is_vertical_ = true;
        else {
            a_ = static_cast<double>(origin_.y - target_.y) / static_cast<double>(origin_.x - target_.x);
            is_vertical_ = false;
        }

        lazy_a_ = false;
    }
    void update_b() {
        if(lazy_a_) update_a();

        if(!is_vertical_)
            b_ = static_cast<double>(origin_.y) - a_ * static_cast<double>(origin_.x);

        lazy_b_ = false;
    }

    // attributes
    double a_;
    double b_;
    bool use_left_as_up_;
    Integer2D origin_;
    Integer2D target_;
    bool is_vertical_;

    // lazyness attributes
    bool lazy_a_;
    bool lazy_b_;
};

// contructors and destructors
EquationalLine::EquationalLine(const Integer2D& origin, const Integer2D& target, bool use_left_as_up)
  : pimpl_(new EquationalLineImpl(origin,target,use_left_as_up)) {}

EquationalLine::EquationalLine(const EquationalLine& copy) : pimpl_(new EquationalLineImpl(*(copy.pimpl_))) {}

EquationalLine::~EquationalLine() { delete pimpl_; }

// getters
double EquationalLine::a() const { return pimpl_->a(); }
double EquationalLine::b() const { return pimpl_->b(); }
bool EquationalLine::use_left_as_up() const { return pimpl_->use_left_as_up(); }
const Integer2D& EquationalLine::origin() const { return pimpl_->origin(); }
const Integer2D& EquationalLine::target() const { return pimpl_->target(); }

// setters
void EquationalLine::set_origin(const Integer2D& origin) { pimpl_->set_origin(origin); }
void EquationalLine::set_target(const Integer2D& target) { pimpl_->set_target(target); }

// methods
double EquationalLine::YAt(double x) const { return pimpl_->YAt(x); }
Ord EquationalLine::CompareWithInteger2D(const Integer2D& vec) { return pimpl_->CompareWithInteger2D(vec); }




} // namespace alg
} // namespace game