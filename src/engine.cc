//
// Created by Brianna Zhang on 4/21/20.
//

#include <set>
#include <stdexcept>

#include <mylibrary/engine.h>

namespace myapp {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {-1, 0};
    case Direction::kDown:
      return {+1, 0};
    case Direction::kLeft:
      return {0, -1};
    case Direction::kRight:
      return {0, +1};
  }

  throw std::out_of_range("switch statement not matched");
}

PacMan Engine::GetPacMan() const { return pacman; }

Engine::Engine(size_t given_width, size_t given_height)
  : Engine{given_width, given_height, static_cast<unsigned>(std::rand())} {}

Engine::Engine(size_t given_width, size_t given_height, unsigned int seed)
    : width{given_width},
      height{given_height},
      direction{Direction::kRight},
      last_direction{Direction::kUp},
      pacman{kStartLoc},
      rng{seed},
      uniform{0, 1} {}

void Engine::Step() {
  Location d_loc = FromDirection(direction);
  Location curr_loc = pacman.GetLocation();
  pacman.SetLocation((curr_loc + d_loc) % Location(width, height)) ;
  last_direction = direction;
}

void Engine::SetDirection(const myapp::Direction given_direction) {
  direction = given_direction;
}


// Retrieves a random location not occupied by the snake.
// This method uses Reservoir sampling.
Location Engine::GetRandomLocation() {\
  int num_open = 0;
  Location final_location(0, 0);

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      Location loc(row, col);

      if (uniform(rng) <= 1./(++num_open)) {
        final_location = loc;
      }
    }
  }

  return final_location;
}
}
