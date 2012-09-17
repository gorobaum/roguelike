#ifndef BADGAME_ALG_LOS_CONE_H_
#define BADGAME_ALG_LOS_CONE_H_

// Inheritance
// (none)

// External Dependencies
#include <list>

// Internal Dependencies
#include "game/alg/equationallinedouble.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/alg.h"
#include "game/base.h"

namespace game {
namespace alg {
namespace los {

namespace enums {

namespace bump {
enum BumpType {
    ABV = 0, // tile está completamente acima do cone de visão
    UPR = 1, // tile colide com a upper line do cone apenas
    MDL = 2, // tile está dentro do cone de visão, sem colidir com nenhuma linha
    BLK = 3, // tile bloqueia o campo de visão completamente (colide com as duas linhas)
    LWR = 4, // tile colide com a lower line do cone apenas
    BLW = 5  // tile está completamente abaixo do cone de visão
};
}

} // namespace enums

class Cone {
  public:
    Cone(const EquationalLineDouble& upper, const EquationalLineDouble& lower);
    ~Cone() {};
    
    enums::bump::BumpType ComputeBumpType(const ugdk::Vector2D& up_left);

    void UpperBump(const ugdk::Vector2D& up_left);
    void LowerBump(const ugdk::Vector2D& up_left);

  private:
    EquationalLineDouble upper_;
    EquationalLineDouble lower_;
    
    std::list<ugdk::Vector2D> upper_bumps_;
    std::list<ugdk::Vector2D> lower_bumps_;
};

} // namespace los
} // namespace alg
} // namespace game

#endif // BADGAME_ALG_LOS_CONE_H_