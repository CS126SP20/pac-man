//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <random>
#include <cinder/app/App.h>
#include <cinder/Vector.h>

#include "direction.h"
#include "map.h"
#include "pacman.h"

#include <vector>

namespace myapp {

using cinder::app::KeyEvent;
const Location kStartLoc{14, 26};

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  void Step();

  // Changes the direction of the snake for the next time step.
  void SetDirection(const Direction given_direction);

  void SetMap(const Map given_map);

  PacMan GetPacMan() const;

  bool IsValidDirection(Direction);

 private:
  Location GetRandomLocation();


 private:
  const size_t width;
  const size_t height;
  Direction direction;
  Direction last_direction;
  Map map;
  PacMan pacman;

  // Not sure what these do but they were in the Snake engine class
  std::mt19937 rng;
  std::uniform_real_distribution<double> uniform;

};

}

#endif  // FINALPROJECT_ENGINE_H
