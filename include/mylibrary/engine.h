//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <random>

#include "direction.h"

namespace myapp {

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  // Changes the direction of the snake for the next time step.
  void SetDirection(const Direction given_direction);

 private:
  const size_t width;
  const size_t height;
  Direction direction;
  Direction last_direction;

  // Not sure what these do but they were in the Snake engine class
  std::mt19937 rng;
  std::uniform_real_distribution<double> uniform;

};

}

#endif  // FINALPROJECT_ENGINE_H
