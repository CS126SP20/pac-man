//
// Created by Brianna Zhang on 4/21/20.
//

#include <mylibrary/engine.h>

namespace myapp {
  Engine::Engine(size_t given_width, size_t given_height)
    : Engine{given_width, given_height, static_cast<unsigned>(std::rand())} {}

  Engine::Engine(size_t given_width, size_t given_height, unsigned int seed)
      : width{given_width},
        height{given_height},
        rng{seed},
        uniform{0, 1} {}

  void Engine::SetDirection(const myapp::Direction given_direction) {
    direction = given_direction;
  }
}
