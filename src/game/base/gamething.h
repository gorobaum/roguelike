#ifndef BADGAME_BASE_GAMETHING_H_
#define BADGAME_BASE_GAMETHING_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

typedef struct {
    bool is_obj_;
    union {
        GameObject* obj_;
        GameTile* tile_;
    } it_;
} GameThing;

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMETHING_H_