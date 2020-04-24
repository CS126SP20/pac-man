#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

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

// Determines if the given directions are complementary.
bool IsOpposite(const Direction lhs, const Direction rhs) {
  return ((lhs == Direction::kUp && rhs == Direction::kDown) ||
          (lhs == Direction::kDown && rhs == Direction::kUp) ||
          (lhs == Direction::kLeft && rhs == Direction::kRight) ||
          (lhs == Direction::kRight && rhs == Direction::kLeft));
}

PacMan Engine::GetPacMan() const { return pacman; }

vector<Ghost> Engine::GetGhosts() const { return ghosts; }

Engine::Engine(size_t given_width, size_t given_height)
    : Engine{given_width, given_height, static_cast<unsigned>(std::rand())} {}

Engine::Engine(size_t given_width, size_t given_height, unsigned seed)
    : width{given_width}, height{given_height},
      pacman{kStartLocPacMan},
      map{},
      rng{seed} {

  for (int i = 0; i < kNumGhosts; i++) {
    ghosts.emplace_back(kStartLocGhost + Location(i, 0));
  }
}

void Engine::Step() {
  Direction pm_curr_d = pacman.GetDirection();

  // If PM tries to move in an invalid direction, he doesn't stop and keeps
  // moving in the same direction he was moving
  if (!IsValidDirection(pm_curr_d)) {
    Direction last_direction = pacman.GetLastDirection();
    pacman.SetDirection(last_direction);
  }

  Location pm_curr_loc = pacman.GetLocation();
  Location pm_d_loc = FromDirection(pm_curr_d);
  Location pm_target_loc = ((pm_curr_loc + pm_d_loc)) % Location(width, height);

  // Changes Pac-Man's location
  char c = map.GetLayout()[pm_target_loc.Col()][pm_target_loc.Row()];
  if (c != '#' && c != '&' && c != '?') {
    pacman.SetLocation(pm_target_loc);
    pacman.SetLastDirection(pm_curr_d);
  }

  Ghost g1 = ghosts.at(0);


}

void Engine::SetMap(const Map& given_map) {
  map = given_map;
}

Direction Engine::SetPMDirection(const Direction& given_direction) {
  pacman.SetLastDirection(pacman.GetDirection());
  pacman.SetDirection(given_direction);
}

bool Engine::IsValidDirection(Direction) {
  Location curr_loc = pacman.GetLocation();
  Location d_loc = FromDirection(pacman.GetDirection());
  Location target_loc = (curr_loc + d_loc) % Location(width, height);

  char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
  return !(c == '#' || c == '&' || c == '?');
}
}

#pragma clang diagnostic pop