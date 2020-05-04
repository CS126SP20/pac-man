//
// Created by Brianna Zhang on 4/22/20.
//

#include <mylibrary/ghost.h>

namespace myapp {

Ghost::Ghost(const Location& given_location)
    : location{given_location},
      direction{Direction::kRight},
      in_box{true} {}

Direction Ghost::GetDirection() const { return direction; }

Direction Ghost::SetDirection(const myapp::Direction& given_direction) {
  direction = given_direction;
  return direction;
}

Location Ghost::GetLocation() const { return location; }

Location Ghost::SetLocation(const myapp::Location &given_location) {
  location = given_location;
  return location;
}

bool Ghost::GetInBox() const { return in_box; }

bool Ghost::SetInBox(const bool& given_bool) {
  in_box = given_bool;
}
}