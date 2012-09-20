#ifndef BADGAME_COMPONENT_SHAPE_H_
#define BADGAME_COMPONENT_SHAPE_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <list> // template class
#include <ugdk/math/integer2D.h>

// Internal Dependencies
// (none)

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
    const std::list<ugdk::math::Integer2D>& occupying_tiles() const { return occupying_tiles_; } 
    std::list<ugdk::math::Integer2D>& occupying_tiles()             { return occupying_tiles_; }

    virtual const ugdk::math::Integer2D& PlaceAt(const ugdk::math::Integer2D& tile) = 0;
    virtual const ugdk::math::Integer2D& Move(const std::list<ugdk::math::Integer2D>& mov) = 0;
    virtual const ugdk::math::Integer2D& Step(const ugdk::math::Integer2D& dir) = 0;

  protected:
    double stay_sizeclass_;
    double pass_sizeclass_;
    double enter_sizeclass_;
	std::list<ugdk::math::Integer2D> occupying_tiles_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_H_