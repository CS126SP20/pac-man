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
const Location kStartLocGhost{12, 14};
const size_t kNumGhosts = 4;

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  void Step();

  void SetMap(const Map& given_map);
  Map GetMap() const;

  PacMan GetPacMan() const;
  std::vector<Ghost> GetGhosts() const;

  Direction SetPMDirection(const Direction& given_direction);

  void SetPoints(const int& new_points);
  int GetPoints() const;

 private:
  void StepPacMan();
  void StepGhosts();
  void UpdateFood();

  std::vector<Direction> GetPossDirections(Ghost ghost);

  Location GetTargetLoc(const Location& loc, const Direction& direction);

  bool IsValidLocation(Location target_loc);

 private:
  const size_t width;
  const size_t height;
  Map map;
  PacMan pacman;
  std::vector<Ghost> ghosts;
  int points;
  std::mt19937 rng;
};

}

#endif  // FINALPROJECT_ENGINE_H
