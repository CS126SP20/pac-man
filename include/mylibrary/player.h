//
// Created by Brianna Zhang on 5/2/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>

namespace myapp {

struct Player{
  Player(const std::string& name, size_t score) : name(name), score(score) {}
  std::string name;
  size_t score;
};

}

#endif  // FINALPROJECT_PLAYER_H
