#ifndef BADGAME_ALG_LOSPROCESSOR_H_
#define BADGAME_ALG_LOSPROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <array>    // control_offsets_
#include <list>     // cones_
#include <map>      // control_offsets_

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/alg.h"
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace alg {

typedef std::array<ugdk::Vector2D,9> Array9Vec2D;

class LoSProcessor {
  public:
    LoSProcessor(component::Vision* vision);
    ~LoSProcessor();

    void Process();

          component::Vision* vision()       { return vision_; }
    const component::Vision* vision() const { return vision_; }
    
    const std::map<int, Array9Vec2D >& control_offsets() const { return control_offsets_; }

  private:
    // returns n_th octant's o'clock notation.
    int nth_orientation(int n) { return n + (n-1)/2; }

    void preprocess(int dir_x, int dir_y, int off_x = 0, int off_y = 0);

    void calculate_control_points(double sight_range);
    void transform1(const Array9Vec2D& base, int dest);
    void transform2(const Array9Vec2D& base, int dest);
    void transform3(const Array9Vec2D& base, int dest);
    void transform4(const Array9Vec2D& base, int dest);

    bool process_cone(const base::GameTile* binded_tile, LoSCone* cone);

    component::Vision* vision_;
    std::array<LoSOctant*,12> octants_;
    std::array<int,16> preprocessings_;

    std::list<LoSCone*> cones_;
    std::map<int, Array9Vec2D > control_offsets_; // (steep_near,steep_far,shallow_near,shallow_far,rotate_offset)

};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSPROCESSOR_H_