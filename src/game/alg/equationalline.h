#ifndef BADGAME_ALG_EQUATIONALLINE_H_
#define BADGAME_ALG_EQUATIONALLINE_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
class game::alg::EquationalLineImpl;
#include <ugdk/math.h>
#include "utils/utils.h"


namespace game {
namespace alg {
    
class EquationalLine {
  public:
    // constructors and destructors
    EquationalLine(double a = 0.0, double b = 0.0, bool use_left_as_up = true);
    EquationalLine(const ugdk::Vector2D& origin, const ugdk::Vector2D& target, bool use_left_as_up = true);
    ~EquationalLine();

    // getters
    double a() const;
    double b() const;
    bool use_left_as_up() const;
    const ugdk::Vector2D& origin() const;
    const ugdk::Vector2D& offset_target() const;

    // setters
    void set_a(double a);
    void set_b(double b);
    void set_origin(const ugdk::Vector2D& new_origin);
    void set_target(const ugdk::Vector2D& new_target);

    // methods
    ugdk::Vector2D Target() const;
    double YAt(double x) const;
    utils::enums::ord::Ord CompareWithVector(const ugdk::Vector2D& vec);

  private:
    EquationalLineImpl*const pimpl_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQUATIONALLINE_H_