//
// Created by Brianna Zhang on 4/22/20.
//

#include <mylibrary/ghost.h>

namespace myapp {

Ghost::Ghost(const Location& given_location)
    : location{given_location} {};

Location Ghost::GetLocation() const { return location; }

void Ghost::SetLocation(const Location &given_location) {
  location = given_location;
}

}