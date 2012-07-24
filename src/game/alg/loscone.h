#ifndef BADGAME_ALG_LOSCONE_H_
#define BADGAME_ALG_LOSCONE_H_

// Inheritance
// (none)

// External Dependencies
#include <list>

// Internal Dependencies
#include "game/alg/eqline.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/alg.h"
#include "game/base.h"

namespace game {
namespace alg {

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

class LoSCone {
  public:
    LoSCone(const EqLine& steep, const EqLine& shallow, int octant,
            const LoSProcessor* owner);

    const EqLine& steep()   const { return   steep_; }
    const EqLine& shallow() const { return shallow_; }

    const int orientation() const { return orientation_; }
    
    const std::list<ugdk::Vector2D>&   steep_bumps() const { return   steep_bumps_; }
    const std::list<ugdk::Vector2D>& shallow_bumps() const { return shallow_bumps_; }

    void   SteepBump(const base::GameTile* tile, int ydir);
    void ShallowBump(const base::GameTile* tile, int ydir);

    enums::bump::BumpType ComputeBumpType(const base::GameTile* focus, int ydir);

#ifdef DEBUG
    void LoSCone::TestCmpBumpType(const LoSProcessor* owner);
#endif

  private:
    LoSCone& operator=(const LoSCone&);

    EqLine steep_;
    EqLine shallow_;
    const int orientation_; // measured as 1,2,4,5,7,8,10 and 11 o'clock.
    const LoSProcessor* owner_;

    std::list<ugdk::Vector2D>   steep_bumps_;
    std::list<ugdk::Vector2D> shallow_bumps_;
};

} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOSCONE_H_