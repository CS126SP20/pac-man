//
// Created by Brianna Zhang on 4/22/20.
//

#ifndef FINALPROJECT_GHOST_H
#define FINALPROJECT_GHOST_H

#include "location.h"

namespace myapp {

class Ghost {
 public:
  explicit Ghost(const Location& given_location);

  Location GetLocation() const;
  void SetLocation(const Location& given_location);

 private:
  Location location;
};
}

#endif  // FINALPROJECT_GHOST_H
