#ifndef BADGAME_ALG_LOSPROCESSOR_H_
#define BADGAME_ALG_LOSPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <array> // control_offsets_
#include <list> // steep_bumps_, shallow_bumps_
#include <map> // control_offsets_
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

typedef std::array<ugdk::Vector2D,5> Array5Vec2D;

class LosProcessor {
  public:
    LosProcessor(component::Vision* vision);
    ~LosProcessor();

    void Process();

          component::Vision* vision()       { return vision_; }
    const component::Vision* vision() const { return vision_; }
    
    const std::map<int, Array5Vec2D >& control_offsets() const { return control_offsets_; }

  private:
    // returns n_th octant's o'clock notation.
    int nth_orientation(int n) { return n + (n-1)/2; }

    void preprocess(int dir_x, int dir_y, int off_x = 0, int off_y = 0);

    void calculate_control_points(double sight_range);
    void transform1(const Array5Vec2D& base, int dest);
    void transform2(const Array5Vec2D& base, int dest);
    void transform3(const Array5Vec2D& base, int dest);
    void transform4(const Array5Vec2D& base, int dest);

    bool process_cone(const base::GameTile* binded_tile, LosCone* cone);

    component::Vision* vision_;
    std::array<LosOctant*,12> octants_;
    std::array<int,16> preprocessings_;

    std::list<LosCone*> cones_;
    std::map<int, Array5Vec2D > control_offsets_; // (steep_near,steep_far,shallow_near,shallow_far,rotate_offset)

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
    LosOctant& operator=(const LosOctant&);

    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.
    const LosProcessor* owner_;
};

class LosOctant::iterator {
  public:
    iterator(const LosOctant* owner, double range_squared);
    ~iterator();

    iterator& operator++();

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

    double range_squared_;
};

namespace enums {
namespace bump {
enum BumpType {
    ABV = 0, // tile está completamente acima do cone de visão
    STP = 1, // tile colide com a steep line do cone apenas
    MDL = 2, // tile está dentro do cone de visão, sem colidir com nenhuma linha
    BLK = 3, // tile bloqueia o campo de visão completamente (colide com as duas linhas)
    SHL = 4, // tile colide com a shallow line do cone apenas
    BLW = 5  // tile está completamente abaixo do cone de visão
};
}
}

class LosCone {
  public:
    LosCone(const EqLine& steep, const EqLine& shallow, int octant,
            const ugdk::Vector2D& straight_block,
            const ugdk::Vector2D& inner_diag_block, const ugdk::Vector2D& outer_diag_block,
            const LosProcessor* owner);

    const EqLine& steep()   const { return   steep_; }
    const EqLine& shallow() const { return shallow_; }

    const int orientation() const { return orientation_; }
    
    const std::list<ugdk::Vector2D>&   steep_bumps() const { return   steep_bumps_; }
    const std::list<ugdk::Vector2D>& shallow_bumps() const { return shallow_bumps_; }

    void   SteepBump(const base::GameTile* tile);
    void ShallowBump(const base::GameTile* tile);

    enums::bump::BumpType ComputeBumpType(const base::GameTile* focus, int ydir);

#ifdef DEBUG
    void LosCone::TestCmpBumpType(const LosProcessor* owner);
#endif

  private:
    LosCone& operator=(const LosCone&);

    EqLine steep_;
    EqLine shallow_;
    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.
    const LosProcessor* owner_;

    std::list<ugdk::Vector2D>   steep_bumps_;
    std::list<ugdk::Vector2D> shallow_bumps_;

    const ugdk::Vector2D& straight_block_;
    const ugdk::Vector2D& inner_diag_block_;
    const ugdk::Vector2D& outer_diag_block_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSPROCESSOR_H_