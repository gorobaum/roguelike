#ifndef ROGUELIKE_COMPONENT_H_
#define ROGUELIKE_COMPONENT_H_

namespace game {
namespace component {

class ComponentBase;

// Controller components
class Controller;
class ControllerAi;
class ControllerIdle;
class ControllerPlayer;
class Vision;

// Model components
class Damageable;
class Energy;
class Shape;
class ShapeRectangular;

// View components
class Graphic;
class GraphicRectangular;



} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_H_