#ifndef ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_
#define ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_

// Inheritance
// (none)

// External Dependencies
#include <queue>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace action {
namespace time {

class obj_less {
  public:
    obj_less() {}
    ~obj_less() {}
    bool operator()(const base::GameObject* a, const base::GameObject* b) const;
};

class TimeManager {
  // singleton
  static TimeManager* reference_;
  TimeManager();

  public:
    static TimeManager* reference() {
        return reference_ == nullptr
          ? (reference_ = new TimeManager())
          : reference_ ;
    }
    ~TimeManager();

  private:
     typedef std::priority_queue< base::GameObject*, std::vector<base::GameObject*>, obj_less >
             ObjectQueue;

     ObjectQueue actors_;
};

} // namespace time
} // namespace action
} // namespace game

#endif /* ROGUELIKE_ACTION_TIME_TIMEMANAGER_H_ */