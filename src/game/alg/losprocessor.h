#ifndef BADGAME_ALG_LOSPROCESSOR_H_
#define BADGAME_ALG_LOSPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <map>  // octants_

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace alg {

class LosOctant;

class LosProcessor {
  public:
          component::Vision* vision()       { return vision_; }
    const component::Vision* vision() const { return vision_; }

  private:
    component::Vision* vision_;
};

class LosOctant;

class LosOctant {
  public:
    LosOctant(int orientation, LosProcessor* owner)
      : orientation_(orientation),
        owner_(owner) {}

    class iterator;

    const int orientation() const { return orientation_; }
    const LosProcessor* owner() const { return owner_; }

  private:
    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.
    const LosProcessor* owner_;
};

class LosOctant::iterator {
  public:
    iterator(const LosOctant* owner);
    ~iterator();

    iterator& operator++();
    base::GameTile* operator*() const { return focus_; }

  private:
    void step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out);

    base::GameTile* focus_;
    base::GameTile* outer_focus_;

    const LosOctant* owner_;

    int count_outer_;
    int count_inner_;

};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSPROCESSOR_H_