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
  explicit Ghost(const Location& given_location);

  Direction GetDirection() const;
  Direction SetDirection(const Direction& given_direction);

  Location GetLocation() const;
  Location SetLocation(const Location& given_location);

 private:
  Location location;
  Direction direction;
};
}

#endif  // FINALPROJECT_GHOST_H
