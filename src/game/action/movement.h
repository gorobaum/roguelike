#ifndef BADGAME_ACTION_MOVEMENT_H_
#define BADGAME_ACTION_MOVEMENT_H_

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