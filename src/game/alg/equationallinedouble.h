#ifndef ROGUELIKE_ALG_EQUATIONALLINEDOUBLE_H_
#define ROGUELIKE_ALG_EQUATIONALLINEDOUBLE_H_

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

class EquationalLineDoubleImpl;
    
class EquationalLineDouble {
  // Lacks operator=
  EquationalLineDouble& operator=(const EquationalLineDouble&);

  public:
    // constructors and destructors
    EquationalLineDouble(const ugdk::Vector2D& origin, const ugdk::Vector2D& target, bool use_left_as_up = true);
    EquationalLineDouble(const EquationalLineDouble& copy);
    ~EquationalLineDouble();

    // getters
    double a() const;
    double b() const;
    bool use_left_as_up() const;
    const ugdk::Vector2D& origin() const;
    const ugdk::Vector2D& target() const;

    // setters
    void set_origin(const ugdk::Vector2D& origin);
    void set_target(const ugdk::Vector2D& target);
    void set_use_left_as_up(bool use_left_as_up);

    // methods
    double YAt(double x) const;
    utils::enums::ord::Ord CompareWith(const ugdk::Vector2D& vec);

  private:
    EquationalLineDoubleImpl*const pimpl_;
};

} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_EQUATIONALLINEDOUBLE_H_