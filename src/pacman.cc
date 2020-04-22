//
// Created by Brianna Zhang on 4/21/20.
//

#include <mylibrary/pacman.h>

namespace myapp {
PacMan::PacMan(const Location& given_location)
    : location{given_location},
      consumed_power_food{false} {}

Location PacMan::GetLocation() const { return location; }

Location PacMan::SetLocation(const myapp::Location& given_location) {
  location = given_location;
  return location;
}

void PacMan::SetVisibility(bool visibility) { visible = visibility; }

bool PacMan::IsVisible() const { return visible; }

bool PacMan::HasConsumedPowerFood(bool update) {
  consumed_power_food = update;
}

}