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

const Location kStartLocPacMan{14, 20};
const Location kStartLocGhost{12, 17};

const size_t kStartScore = 0;
const size_t kNumGhosts = 4;

const size_t kNormalFoodPts = 10;
const size_t kSpecialFoodPts = 50;
const size_t kCherryPts = 100;
const size_t kGhostPts = 200;

class Engine {
 public:
  // Constructors for Engine
  Engine(size_t given_width, size_t given_height);
  Engine(size_t given_width, size_t given_height, unsigned seed);

  // Represents a 'step' in the game; essentially updates the game
  void Step();

  // Checks for collisions between PacMan and the ghosts
  void CheckCollisions();

  // Checks whether or not a level has been won
  bool HasWon() const;

  // Resets PacMan and the ghosts' locations for when PacMan collides with a ghost
  void Reset();

  // Resets PacMan and the ghosts' locations, food, number of lives, score, and
  // the hit_ghost and ate_special_food booleans
  void ResetAll();

  /* == GETTERS == */
  // Gets PacMan
  PacMan GetPacMan() const;

  // Gets the ghosts
  std::vector<Ghost> GetGhosts() const;

  // Gets the map
  Map GetMap() const;

  // Gets the score
  size_t GetScore() const;

  // Gets whether or not PacMan has eaten 'special' food
  bool GetAteSpecialFood() const;

  // Gets whether or not PacMan has hit a ghost
  bool GetHitGhost() const;

  /* == SETTERS == */
  // Sets the direction of PacMan
  Direction SetDirection(const Direction& given_direction);

  // Sets the map
  void SetMap(const Map& given_map);

  // Sets whether or not PacMan has eaten 'special' food
  void SetAteSpecialFood(const bool& given_bool);

 private:
  // Steps PacMan
  void StepPacMan();

  // Steps the ghosts
  void StepGhosts();

  // Checks if PacMan's current location has food. If so, eat the food and
  // subsequently update the score & the food on the map
  void EatFood();

  // Gets possible directions that a given ghost can move in
  std::vector<Direction> GetPossDirections(Ghost ghost);

  // Gets the the target location based on a given current location and given
  // current direction
  Location GetTargetLoc(const Location& loc, const Direction& direction);

 private:
  const size_t width;
  const size_t height;
  size_t score;
  std::mt19937 rng;

  PacMan pacman;
  std::vector<Ghost> ghosts;
  Map map;

  bool ate_special_food;
  bool hit_ghost;
};
}

#endif  // FINALPROJECT_ENGINE_H
