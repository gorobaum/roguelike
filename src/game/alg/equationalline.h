#ifndef ROGUELIKE_ALG_EQUATIONALLINE_H_
#define ROGUELIKE_ALG_EQUATIONALLINE_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "utils/utils.h"

namespace game {
namespace alg {

class EquationalLineImpl;
    
class EquationalLine {
  // Lacks operator=
  EquationalLine& operator=(const EquationalLine&);

  public:
    // constructors and destructors
    EquationalLine(const ugdk::math::Integer2D& origin, const ugdk::math::Integer2D& target, bool use_left_as_up = true);
    EquationalLine(const EquationalLine& copy);
    ~EquationalLine();

    // getters
    double a() const;
    double b() const;
    bool use_left_as_up() const;
    const ugdk::math::Integer2D& origin() const;
    const ugdk::math::Integer2D& target() const;

    // setters
    void set_origin(const ugdk::math::Integer2D& origin);
    void set_target(const ugdk::math::Integer2D& target);
    void set_use_left_as_up(bool use_left_as_up);

    // methods
    double YAt(double x) const;
    utils::enums::ord::Ord CompareWithInteger2D(const ugdk::math::Integer2D& vec);

  private:
    EquationalLineImpl*const pimpl_;
};

} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_EQUATIONALLINE_H_