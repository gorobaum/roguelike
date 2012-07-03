#ifndef BADGAME_ALG_LOSPROCESSOR_H_
#define BADGAME_ALG_LOSPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <list> // steep_bumps_, shallow_bumps_
#include <vector> // octants_

// Internal Dependencies
#include "game/alg/eqline.h"

// Forward Declarations
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace alg {

class LosOctant;
class LosCone;

class LosProcessor {
  public:
    LosProcessor(component::Vision* vision);
    ~LosProcessor();

    void Process();

          component::Vision* vision()       { return vision_; }
    const component::Vision* vision() const { return vision_; }

  private:
    int nth_orientation(int n) {
        switch(n) {
            case 8: case 7: return n+3;
            case 6: case 5: return n+2;
            case 4: case 3: return n+1;
            case 2: case 1: return n;
            default: return 0;
        }
    }

    void preprocess(int dir_x, int dir_y, int off_x = 0, int off_y = 0);

    component::Vision* vision_;
    std::vector<LosOctant*> octants_;
    std::vector<int> preprocessings_;
};

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
    iterator& jump();

    const base::GameTile* operator*() const { return focus_; }
    const base::GameTile* outer_focus() const { return outer_focus_; }

  private:
    void step(int delta_x_in, int delta_y_in, int delta_x_out, int delta_y_out);
    void step_jump(int delta_x_out, int delta_y_out);

    base::GameTile* focus_;
    base::GameTile* outer_focus_;

    const LosOctant* owner_;

    int count_outer_;
    int count_inner_;
};


class LosCone {
  public:
    LosCone(const EqLine& steep, const EqLine& shallow, int octant,
            const ugdk::Vector2D& straight_block,
            const ugdk::Vector2D& inner_diag_block, const ugdk::Vector2D& outer_diag_block)
      : steep_(steep), shallow_(shallow), orientation_(octant), steep_bumps_(), shallow_bumps_(),
        straight_block_(straight_block), inner_diag_block_(inner_diag_block), outer_diag_block_(outer_diag_block) {}

    const EqLine& steep()   const { return   steep_; }
    const EqLine& shallow() const { return shallow_; }

    int orientation() const { return orientation_; }
    
    const std::list<ugdk::Vector2D>&   steep_bumps() const { return   steep_bumps_; }
    const std::list<ugdk::Vector2D>& shallow_bumps() const { return shallow_bumps_; }

    void   steep_bump(const ugdk::Vector2D& limit) {
        steep_.set_target(limit);
        for(auto st = shallow_bumps_.end(); st != shallow_bumps_.begin();) {
            --st;
            if(steep_.CompareWithVector(*st) <= 0) {
                steep_.set_origin(*st);
                shallow_bumps_.erase(shallow_bumps_.begin(),++st);
                break;
            }
        }
        steep_bumps_.push_back(limit);
    }

    void shallow_bump(const ugdk::Vector2D& limit) {
        shallow_.set_target(limit);
        for(auto st = steep_bumps_.end(); st != steep_bumps_.begin();) {
            --st;
            if(shallow_.CompareWithVector(*st) >= 0) {
                shallow_.set_origin(*st);
                steep_bumps_.erase(steep_bumps_.begin(),++st);
                break;
            }
        }
        shallow_bumps_.push_back(limit);
    }

  private:
    EqLine steep_;
    EqLine shallow_;
    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.

    std::list<ugdk::Vector2D>   steep_bumps_;
    std::list<ugdk::Vector2D> shallow_bumps_;

    const ugdk::Vector2D& straight_block_;
    const ugdk::Vector2D& inner_diag_block_;
    const ugdk::Vector2D& outer_diag_block_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSPROCESSOR_H_