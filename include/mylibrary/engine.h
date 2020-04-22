//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <random>
#include <cinder/app/App.h>
#include <cinder/Vector.h>

#include "direction.h"
#include "pacman.h"

#include <vector>

namespace myapp {

using cinder::app::KeyEvent;
const Location kStartLoc{14, 18};

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  // Changes the direction of the snake for the next time step.
  void SetDirection(const Direction given_direction);

  PacMan GetPacMan() const;

 private:
  const size_t width;
  const size_t height;
  PacMan pacman;
  Direction direction;
  Direction last_direction;

  // Not sure what these do but they were in the Snake engine class
  std::mt19937 rng;
  std::uniform_real_distribution<double> uniform;

};

}

#endif  // FINALPROJECT_ENGINE_H
