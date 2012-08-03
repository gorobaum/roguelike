#ifndef BADGAME_ALG_EQUATIONALLINE_H_
#define BADGAME_ALG_EQUATIONALLINE_H_

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
  public:
    // constructors and destructors
    EquationalLine(const ugdk::Vector2D& origin, const ugdk::Vector2D& target, bool use_left_as_up = true);
    ~EquationalLine();

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
    utils::enums::ord::Ord CompareWithVector(const ugdk::Vector2D& vec);

  private:
    EquationalLine& operator=(const EquationalLine&);

    EquationalLineImpl*const pimpl_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQUATIONALLINE_H_