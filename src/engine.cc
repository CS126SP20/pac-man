#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-trailing-return-type"
//
// Created by Brianna Zhang on 4/21/20.
//

#include <cmath>
#include <stdexcept>

#include <mylibrary/engine.h>

namespace myapp {

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

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
      ate_special_food{false}, hit_ghost{false},
      rng{seed} {

  for (int i = 0; i < kNumGhosts; i++) {
    Ghost ghost = Ghost(kStartLocGhost + Location(i, 0));
    ghosts.push_back(ghost);
  }
}

void Engine::Step() {
  CheckCollisions();
  EatFood();
  StepPacMan();
  StepGhosts();
}

void Engine::StepPacMan() {
  Direction curr_d = pacman.GetDirection();
  Location curr_loc = pacman.GetLocation();
  Location target_loc = GetTargetLoc(curr_loc, curr_d);

  // If PM tries to move in an invalid direction, he doesn't stop and keeps
  // moving in the same direction he was moving
  char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];

  if ((c == '#' || c == '&' || c == '?')) {
    Direction last_direction = pacman.GetLastDirection();
    pacman.SetDirection(last_direction);
  }

  if (!(c == '#' || c == '&' || c == '?')) {
    pacman.SetLocation(target_loc);
    pacman.SetLastDirection(curr_d);
  }
}

void Engine::Reset() {
  pacman.SetLocation(kStartLocPacMan);
  pacman.SetDirection(Direction::kUp);
  hit_ghost = false;

  for (int i = 0; i < ghosts.size(); i++) {
    Location loc = Location(kStartLocGhost.Row() + i, kStartLocGhost.Col());
    ghosts.at(i).SetLocation(loc);
    ghosts.at(i).SetInBox(true);
  }
}

void Engine::StepGhosts() {
  for (int i = 0; i < kNumGhosts; i++) {
    Location curr_loc = ghosts.at(i).GetLocation();
    Direction curr_d = ghosts.at(i).GetDirection();

    // This means the ghost is not in the starting box
    if (!(curr_loc.Row() > 10 && curr_loc.Row() < 17 && curr_loc.Col() > 15
        && curr_loc.Col() < 19)) {
      ghosts.at(i).SetInBox(false);
    }

    vector<Direction> poss_d = GetPossDirections(ghosts.at(i));

    // This means that the ghost is at an intersection
    if (poss_d.size() == 1 || poss_d.size() == 2) {
      poss_d.push_back(ghosts.at(i).GetDirection());

      // Assign a random direction
      auto rand_index = rand() % (poss_d.size() - 1);
      Direction new_d = poss_d.at(rand_index);
      Location target_loc = GetTargetLoc(curr_loc, new_d);

      char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
      if (!(c == '#' || c == '?')) {
        ghosts.at(i).SetLocation(target_loc);
        ghosts.at(i).SetDirection(new_d);
      }
    } else {
      // Continue to move in the same direction
      Location target_loc = GetTargetLoc(curr_loc, curr_d);

      char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
      if (!(c == '#' || c == '?')) {
        ghosts.at(i).SetLocation(target_loc);
      }
    }
  }
}

void Engine::EatFood() {
  Location curr_loc = pacman.GetLocation();

  // If Pac-Man's current location contains food, eat food
  std::vector<Food> food = map.GetFood();

  for (int i = 0; i < food.size(); i++) {
    if (food.at(i).GetLocation() == curr_loc) {
      if (food.at(i).GetFoodType() == FoodType::kNormal) {
        score += 10;
        food.erase(food.begin() + i);
        map.SetFood(food);
        break;

      } else if (food.at(i).GetFoodType() == FoodType::kCherry) {
        score += 100;
        food.erase(food.begin() + i);
        map.SetFood(food);
        break;

      } else if (food.at(i).GetFoodType() == FoodType::kSpecial) {
        score += 50;
        food.erase(food.begin() + i);
        map.SetFood(food);
        ate_special_food = true;
        break;
      }
    }
  }
}

void Engine::CheckCollisions() {
  Location curr_loc = pacman.GetLocation();

  for (int i = 0; i < ghosts.size(); i++) {
    if (curr_loc == ghosts.at(i).GetLocation()) {
      if (ate_special_food) {
        ghosts.at(i).SetInBox(true);
        score += 200;
        Location target_loc = Location(kStartLocGhost.Row() + i, kStartLocGhost.Col());
        ghosts.at(i).SetLocation(target_loc);

      } else {
        int curr_lives = pacman.GetLives();
        pacman.SetLives(curr_lives - 1);
        hit_ghost = true;
      }
    }
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


      char c = map.GetLayout()[target_loc.Col()][target_loc.Row()];
      if (ghost.GetInBox()) {
        if (!(c == '#' || c == '?')) {
          poss_d.push_back(direction);
        }

      } else {
        if (!(c == '#' || c == '&' || c == '?')) {
          poss_d.push_back(direction);
        }
      }
    }
  }
  return poss_d;
}

Location Engine::GetTargetLoc(const Location& curr_loc, const Direction& curr_d) {
  Location d_loc = FromDirection(curr_d);
  return ((curr_loc + d_loc)) % Location(height, width);
}

void Engine::SetMap(const Map& given_map) {
  map = given_map;
  map.SetFood(given_map.GetFood());
}

Map Engine::GetMap() const { return map; }

size_t Engine::GetScore() const { return score; }

Direction Engine::SetPMDirection(const Direction& given_direction) {
  pacman.SetLastDirection(pacman.GetDirection());
  pacman.SetDirection(given_direction);
}

bool Engine::GetAteSpecialFood() const { return ate_special_food; }

void Engine::SetAteSpecialFood(const bool &given_bool) {
  ate_special_food = given_bool;
}

bool Engine::GetHitGhost() const { return hit_ghost; }

void Engine::SetHitGhost(const bool& given_bool) {
  hit_ghost = given_bool;
}

}

#pragma clang diagnostic pop