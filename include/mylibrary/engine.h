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
const size_t kNumGhosts = 4;
const size_t kStartScore = 0;

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  void Step();

  void CheckCollisions();

  void SetMap(const Map& given_map);
  Map GetMap() const;

  PacMan GetPacMan() const;
  std::vector<Ghost> GetGhosts() const;

  Direction SetPMDirection(const Direction& given_direction);

  bool GetAteSpecialFood() const;
  void SetAteSpecialFood(const bool& given_bool);

  size_t GetScore() const;

  bool GetHitGhost() const;

  void SetHitGhost(const bool& given_bool);

  bool HasWon() const;

  // Occurs when Pac-Man loses a life:
  // Pac-Man starts at the original location and ghosts start in the box,
  // but nothing else resets
  void Reset();

  void ResetAll();

 private:
  void StepPacMan();
  void StepGhosts();
  void EatFood();

  std::vector<Direction> GetPossDirections(Ghost ghost);

  Location GetTargetLoc(const Location& loc, const Direction& direction);

 private:
  const size_t width;
  const size_t height;
  Map map;
  PacMan pacman;
  std::vector<Ghost> ghosts;

  bool ate_special_food;
  bool hit_ghost;

  size_t score;
  std::mt19937 rng;
};

}

#endif  // FINALPROJECT_ENGINE_H
