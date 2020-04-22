#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_PACMAN_H
#define FINALPROJECT_PACMAN_H

#include "location.h"

namespace myapp {

class PacMan {
 public:
  explicit PacMan(const Location& given_location);

  Location GetLocation() const;
  Location SetLocation(const Location& given_location);

 private:
  Location location;
};
} // namespace myapp


#endif  // FINALPROJECT_PACMAN_H

#pragma clang diagnostic pop