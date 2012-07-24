#ifndef BADGAME_COMPONENT_SHAPE_H_
#define BADGAME_COMPONENT_SHAPE_H_

// Inheritance
#include "game/components/componentbase.h"

// External Dependencies
#include <list> // template class

// Internal Dependencies
#include "game/action/movement.h"   // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Shape : public ComponentBase {
  typedef ComponentBase super;
  public:
    Shape(game::base::GameObject* owner, double stay_sizeclass = 1.0, double pass_sizeclass = 0.25, double enter_sizeclass = 1.0e-5 )
      : super(owner), stay_sizeclass_(stay_sizeclass), pass_sizeclass_(pass_sizeclass), enter_sizeclass_(enter_sizeclass) {}
    ~Shape() {}

    void set_stay_sizeclass(  double stay_sizeclass ) { stay_sizeclass_  = stay_sizeclass;  }
    void set_pass_sizeclass(  double pass_sizeclass ) { pass_sizeclass_  = pass_sizeclass;  }
    void set_enter_sizeclass( double enter_sizeclass) { enter_sizeclass_ = enter_sizeclass; }

    double stay_sizeclass()  const { return stay_sizeclass_;  }
    double pass_sizeclass()  const { return pass_sizeclass_;  }
    double enter_sizeclass() const { return enter_sizeclass_; }
    const std::list<game::base::GameTile*>& occupying_tiles() const { return occupying_tiles_; } 

    virtual game::base::GameTile* PlaceAt(game::base::GameTile* tile) = 0;
    virtual game::base::GameTile* Move(game::action::Movement& mov) = 0;
    virtual game::base::GameTile* Step(game::action::Movement::Direction dir) = 0;

  protected:
    double stay_sizeclass_;
    double pass_sizeclass_;
    double enter_sizeclass_;
	std::list<game::base::GameTile*> occupying_tiles_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_H_