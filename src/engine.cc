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

vector<Ghost> Engine::GetGhosts() const { return ghosts; }

Engine::Engine(size_t given_width, size_t given_height)
  : Engine{given_width, given_height, static_cast<unsigned>(std::rand())} {}

Engine::Engine(size_t given_width, size_t given_height, unsigned int seed)
    : width{given_width}, height{given_height},
      direction{Direction::kRight}, last_direction{Direction::kUp},
      pacman{kStartLocPacMan},
      map{},
      rng{seed},
      uniform{0, 1} {

  for (int i = 0; i < 4; i++) {
    ghosts.emplace_back(kStartLocGhost + Location(i, 0));
  }
}

void Engine::Step() {
  if (!IsValidDirection(direction)) {
    direction = last_direction;
  }

  Location curr_loc = pacman.GetLocation();
  Location d_loc = FromDirection(direction);
  Location target_loc = ((curr_loc + d_loc)) % Location(width, height);

  char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
  if (c != '#' && c != '&' && c != '?') {
    pacman.SetLocation(target_loc);
    last_direction = direction;
  }
}

void Engine::SetDirection(const myapp::Direction given_direction) {
  direction = given_direction;
}

void Engine::SetMap(const Map given_map) {
  map = given_map;
}

bool Engine::IsValidDirection(Direction) {
  Location curr_loc = pacman.GetLocation();
  Location d_loc = FromDirection(direction);
  Location target_loc = (curr_loc + d_loc) % Location(width, height);

  char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
  return !(c == '#' || c == '&' || c == '?');
}

// Retrieves a random location not occupied by PacMan.
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
