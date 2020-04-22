#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

#include <mylibrary/pacman.h>

namespace myapp {

PacMan::PacMan(const Location& given_location)
    : location{given_location} {}

Location PacMan::GetLocation() const { return location; }

Location PacMan::SetLocation(const myapp::Location& given_location) {
  location = given_location;
  return location;
}
}
#pragma clang diagnostic pop