//
// Created by Brianna Zhang on 4/22/20.
//

#ifndef FINALPROJECT_GHOST_H
#define FINALPROJECT_GHOST_H

#include "direction.h"
#include "location.h"

namespace myapp {

class Ghost {
 public:
  // Constructor
  explicit Ghost(const Location& given_location);

  // Getter and setter for the current direction of Ghost
  Direction GetDirection() const;
  Direction SetDirection(const Direction& given_direction);

  // Getter and setter for the location of Ghost
  Location GetLocation() const;
  Location SetLocation(const Location& given_location);

  // Getter and setter for the boolean of whether or not Ghost is in a box
  bool GetInBox() const;
  bool SetInBox(const bool& given_bool);

 private:
  Location location;
  Direction direction;

  // Represents whether or not a ghost is in the starting box
  bool in_box;
};
}

#endif  // FINALPROJECT_GHOST_H
