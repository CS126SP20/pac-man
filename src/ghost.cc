//
// Created by Brianna Zhang on 4/22/20.
//

#include <mylibrary/ghost.h>

namespace myapp {

Ghost::Ghost(const Location& given_location)
    : location{given_location},
      direction{Direction::kRight} {}

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

}