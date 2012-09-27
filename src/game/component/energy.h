#ifndef ROGUELIKE_COMPONENT_ENERGY_H_
#define ROGUELIKE_COMPONENT_ENERGY_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Energy : public ComponentBase {
  typedef ComponentBase super;
  public:
    Energy(game::base::GameObject* owner)
      : super(owner),
                arms_(1.0),         legs_(1.0),         eyes_(1.0),
            max_arms_(1.0),     max_legs_(1.0),     max_eyes_(1.0),
          regen_arms_(1.0),   regen_legs_(1.0),   regen_eyes_(1.0),
          time_carry_(0.0),
        arms_savings_(0.0), legs_savings_(0.0), eyes_savings_(0.0) {}
    ~Energy() {}

    // Getters
    double       arms() const { return       arms_; }
    double       legs() const { return       legs_; }
    double       eyes() const { return       eyes_; }
    double   max_arms() const { return   max_arms_; }
    double   max_legs() const { return   max_legs_; }
    double   max_eyes() const { return   max_eyes_; }
    double regen_arms() const { return regen_arms_; }
    double regen_legs() const { return regen_legs_; }
    double regen_eyes() const { return regen_eyes_; }

    // Setters
    void       set_arms(double       arms) {       arms_ =       arms; }
    void       set_legs(double       legs) {       legs_ =       legs; }
    void       set_eyes(double       eyes) {       eyes_ =       eyes; }
    void   set_max_arms(double   max_arms) {   max_arms_ =   max_arms; }
    void   set_max_legs(double   max_legs) {   max_legs_ =   max_legs; }
    void   set_max_eyes(double   max_eyes) {   max_eyes_ =   max_eyes; }
    void set_regen_arms(double regen_arms) { regen_arms_ = regen_arms; }
    void set_regen_legs(double regen_legs) { regen_legs_ = regen_legs; }
    void set_regen_eyes(double regen_eyes) { regen_eyes_ = regen_eyes; }

    void    set_time_carry(double   time_carry) {   time_carry_ =   time_carry; }
    void set_arms_savings_(double arms_savings) { arms_savings_ = arms_savings; }
    void set_legs_savings_(double legs_savings) { legs_savings_ = legs_savings; }
    void set_eyes_savings_(double eyes_savings) { eyes_savings_ = eyes_savings; }

    // Useful stuff
    double Mean() const { return (arms_ + legs_ + eyes_) / 3.0 ; }

    double   PopTimeCarry() { double ret =   time_carry_;   time_carry_ = 0.0; return ret; }
    double PopArmsSavings() { double ret = arms_savings_; arms_savings_ = 0.0; return ret; }
    double PopLegsSavings() { double ret = legs_savings_; legs_savings_ = 0.0; return ret; }
    double PopEyesSavings() { double ret = eyes_savings_; eyes_savings_ = 0.0; return ret; }

  private:
    double arms_;
    double legs_;
    double eyes_;

    double max_arms_;
    double max_legs_;
    double max_eyes_;

    double regen_arms_;
    double regen_legs_;
    double regen_eyes_;

    double time_carry_;
    double arms_savings_;
    double legs_savings_;
    double eyes_savings_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_VISION_H_