#ifndef BADGAME_ALG_LOSOCTANT_H_
#define BADGAME_ALG_LOSOCTANT_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"
#include "game/alg.h"

namespace game {
namespace alg {

class LoSOctant {
  public:
    LoSOctant(int orientation, LoSProcessor* owner)
      : orientation_(orientation),
        owner_(owner) {}

    class iterator;

    const int orientation() const { return orientation_; }
    const LoSProcessor* owner() const { return owner_; }

  private:
    LoSOctant& operator=(const LoSOctant&);

    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.
    const LoSProcessor* owner_;
};

class LoSOctant::iterator {
  public:
    iterator(const LoSOctant* owner, double range_squared);
    ~iterator();

    iterator& operator++();

    const base::GameTile* operator*() const { return focus_; }
    const base::GameTile* outer_focus() const { return outer_focus_; }
    int count_outer() const { return count_outer_; }
    int count_inner() const { return count_inner_; }

  private:
    void step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out);
    void step_jump(int delta_x_out, int delta_y_out);

    base::GameTile* focus_;
    base::GameTile* outer_focus_;

    const LoSOctant* owner_;

    int count_outer_;
    int count_inner_;

    double range_squared_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSOCTANT_H_