//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_PACMAN_H
#define FINALPROJECT_PACMAN_H

#include "location.h"

namespace myapp {

class PacMan {
 public:
  PacMan(const Location& given_location);

  Location GetLocation() const;
  Location SetLocation(const Location& location);
  void SetVisibility(bool visibility);
  bool IsVisible() const;
  bool HasConsumedPowerFood(bool update);

 private:
  Location location;
  bool consumed_power_food;
  bool visible;

};
} // namespace myapp


#endif  // FINALPROJECT_PACMAN_H
