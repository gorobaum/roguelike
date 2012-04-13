#ifndef BADGAME_ACTION_MOVEMENT_H_
#define BADGAME_ACTION_MOVEMENT_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {

struct Movement {
	enum Direction {
		UP, DOWN, RIGHT, LEFT
	};

	std::list<Direction> dirs;
};

} // namespace action
} // namespace game

#endif // BADGAME_ACTION_MOVEMENT_H_