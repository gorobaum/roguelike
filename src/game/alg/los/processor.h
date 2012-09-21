#ifndef ROGUELIKE_ALG_LOS_PROCESSOR_H_
#define ROGUELIKE_ALG_LOS_PROCESSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <array>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/alg.h"
#include "game/component.h"

namespace game {
namespace alg {
namespace los {

class Processor {
  public:
    Processor(component::Vision* vision);
    ~Processor();

    void Process();

  private:
    component::Vision* vision_;
    std::array<OctantProcessor*,8> octants_;
};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_PROCESSOR_H_