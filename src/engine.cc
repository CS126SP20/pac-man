#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

#include <cmath>
#include <map>
#include <stdexcept>

#include <mylibrary/engine.h>

namespace myapp {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, +1};
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {+1, 0};
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

  for (int i = 0; i < 1; i++) {
    Ghost ghost = Ghost(kStartLocGhost + Location(i, 0));
    ghosts.push_back(ghost);
  }
}

void Engine::Step() {
  StepPacMan();
  StepGhosts();
}

void Engine::StepPacMan() {
  Direction curr_d = pacman.GetDirection();
  Location curr_loc = pacman.GetLocation();
  Location target_loc = GetTargetLoc(curr_loc, curr_d);

  // If PM tries to move in an invalid direction, he doesn't stop and keeps
  // moving in the same direction he was moving
  if (!IsValidLocation(target_loc)) {
    Direction last_direction = pacman.GetLastDirection();
    pacman.SetDirection(last_direction);
  }

  if (IsValidLocation(target_loc)) {
    pacman.SetLocation(target_loc);
    pacman.SetLastDirection(curr_d);
  }
}

void Engine::StepGhosts() {
  vector<Direction> poss_d = GetPossDirections(ghosts.at(0));

  Location curr_loc = ghosts.at(0).GetLocation();
  Direction curr_d = ghosts.at(0).GetDirection();

  // This means that the ghost is at an intersection
  if (poss_d.size() == 1 || poss_d.size() == 2) {
    // Assign a random direction with the directions that bring the ghost closer
    // to Pac-Man having a higher probability of being selected
    Direction new_d = SetRandDirection(poss_d, ghosts.at(0));
    Location target_loc = GetTargetLoc(curr_loc, new_d);

    ghosts.at(0).SetLocation(target_loc);

  } else {
    // Continue to move in the same direction
    Location target_loc = GetTargetLoc(curr_loc, curr_d);
    ghosts.at(0).SetLocation(target_loc);
  }
}

std::vector<Direction> Engine::GetPossDirections(Ghost ghost) {
  std::vector<Direction> poss_d;

  Location curr_loc = ghost.GetLocation();
  Direction curr_d = ghost.GetDirection();
  std::vector<Direction> directions = {Direction::kUp, Direction::kDown,
                                       Direction::kLeft, Direction::kRight};

  for (auto & direction : directions) {
    if (direction != curr_d && !(IsOpposite(direction, curr_d))) {

      Location target_loc = GetTargetLoc(curr_loc, direction);
      if (IsValidLocation(target_loc)) {
        poss_d.push_back(direction);
      }
    }
  }
  return poss_d;
}

Direction Engine::SetRandDirection(std::vector<Direction> &poss_d,
                                   const Ghost &ghost) {
  // Include the current direction in possible directions the ghost can move in
  poss_d.push_back(ghost.GetDirection());
  std::map<Direction, int> direction_weights;

  std::vector<Direction> weighted_d;

  Location pacman_loc = pacman.GetLocation();
  Location ghost_loc = ghost.GetLocation();
  double distance = FindDistance(pacman_loc, ghost_loc);

  auto rand_int = rand() % poss_d.size();
  return poss_d.at(rand_int);
  //for (auto & i : poss_d) {
  /*
  Location ghost_target_loc = GetTargetLoc(ghost_loc, i, true);
  double new_distance = FindDistance(pacman_loc, ghost_target_loc);

  if (new_distance < distance) {
    weighted_d.push_back(i);
    return i;
  }*/
  //}
}

Location Engine::GetTargetLoc(const Location& curr_loc, const Direction& curr_d) {
  Location d_loc = FromDirection(curr_d);
  return ((curr_loc + d_loc)) % Location(height, width);
}

bool Engine::IsValidLocation(Location target_loc) {
  char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
  return !(c == '#' || c == '&' || c == '?');
}

void Engine::SetMap(const Map& given_map) {
  map = given_map;
}

Direction Engine::SetPMDirection(const Direction& given_direction) {
  pacman.SetLastDirection(pacman.GetDirection());
  pacman.SetDirection(given_direction);
}

double Engine::FindDistance(const Location& curr_loc, const Location& target_loc) {
  auto x1 = static_cast<double>(curr_loc.Row());
  auto y1 = static_cast<double>(curr_loc.Col());

  auto x2 = static_cast<double>(target_loc.Row());
  auto y2 = static_cast<double>(target_loc.Col());

  return sqrt(pow(2.0, (x2 - x1)) + pow(2.0, (y2 - y1)));
}
}

#pragma clang diagnostic pop