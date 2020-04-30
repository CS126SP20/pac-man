#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

#include <mylibrary/pacman.h>

namespace myapp {

PacMan::PacMan(const Location& given_location)
    : num_lives{kNumLives},
      location{given_location},
      direction{}, last_direction{Direction::kUp} {}

int PacMan::GetLives() const { return num_lives; }

void PacMan::SetLives(const int& given_lives) {
  num_lives = given_lives;
}

Direction PacMan::GetDirection() const { return direction; }

Direction PacMan::SetDirection(const myapp::Direction& given_direction) {
  direction = given_direction;
  return direction;
}

Direction PacMan::GetLastDirection() const { return last_direction; }

Direction PacMan::SetLastDirection(const myapp::Direction& given_direction) {
  last_direction = given_direction;
  return last_direction;
}

Location PacMan::GetLocation() const { return location; }

Location PacMan::SetLocation(const myapp::Location& given_location) {
  location = given_location;
  return location;
}
}
#pragma clang diagnostic pop