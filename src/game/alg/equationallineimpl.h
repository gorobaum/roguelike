#ifndef BADGAME_ALG_EQUATIONALLINEIMPL_H_
#define BADGAME_ALG_EQUATIONALLINEIMPL_H_

// Inheritance
// (none)

// External Dependencies
#include <array> // lazy_origin_, lazy_target_
#include <ugdk/math/vector2D.h> // origin_, target_

// Internal Dependencies
#include "utils/utils.h"

// Forward Declarations
// (none)

// Defines
// (none>

namespace game {
namespace alg {
    
class EquationalLineImpl {
  public:

  private:
    // utility functions for lazyness
    void update_a() {}
    void update_b() {}
    void update_use_left_as_up() {}
    void update_origin() {}
    void update_diff_target() {}

    // attributes
    double a_;
    double b_;
    bool use_left_as_up_;
    ugdk::Vector2D origin_;
    ugdk::Vector2D diff_target_; // is also a director vector for the line, origin_ + diff_target_ == target()
    //Vector2D dir_vector_norm_;

    bool lazy_a_;
    bool lazy_b_;
    std::array<bool,2> lazy_origin_;
    std::array<bool,2> lazy_diff_target_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_EQUATIONALLINEIMPL_H_