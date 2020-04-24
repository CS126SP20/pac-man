//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <random>
#include <cinder/app/App.h>
#include <cinder/Vector.h>

#include "direction.h"
#include "ghost.h"
#include "map.h"
#include "pacman.h"

#include <vector>

namespace myapp {

using cinder::app::KeyEvent;
const Location kStartLocPacMan{14, 26};
const Location kStartLocGhost{12, 17};
const size_t kNumGhosts = 4;

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  void Step();

  void SetMap(const Map& given_map);

  PacMan GetPacMan() const;

  std::vector<Ghost> GetGhosts() const;

  Direction SetPMDirection(const Direction& given_direction);

  bool IsValidDirection(Direction);

 private:
  const size_t width;
  const size_t height;
  Map map;
  PacMan pacman;
  std::vector<Ghost> ghosts;
  std::mt19937 rng;
};

}

#endif  // FINALPROJECT_ENGINE_H
