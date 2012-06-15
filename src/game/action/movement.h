#ifndef BADGAME_ACTION_MOVEMENT_H_
#define BADGAME_ACTION_MOVEMENT_H_

// Inheritance
// (none)

// External Dependencies
#include <list> // needed for dirs

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {

struct Movement {
	enum Direction {
		NONE = 0, UP = 1, DOWN = 2, LEFT = 3, UP_LEFT = 4,
        DOWN_LEFT = 5, RIGHT = 6, UP_RIGHT = 7, DOWN_RIGHT = 8
	};
	std::list<Direction> dirs;
};

} // namespace action
} // namespace game

#endif // BADGAME_ACTION_MOVEMENT_H_