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
const int kUnweightedProb = 20;

class Engine {
 public:
  Engine(size_t given_width, size_t given_height);

  Engine(size_t given_width, size_t given_height, unsigned seed);

  void Step();

  void StepPacMan();

  void StepGhosts();

  void SetMap(const Map& given_map);

  PacMan GetPacMan() const;

  std::vector<Ghost> GetGhosts() const;

  Direction SetPMDirection(const Direction& given_direction);

  std::vector<Direction> GetPossDirections(Ghost ghost);

  Direction SetRandDirection(std::vector<Direction> poss_d, const Ghost &ghost);

  Location GetTargetLoc(const Location& loc, const Direction& direction);

  double FindDistance(const Location& curr_loc, const Location& target_loc);

  bool IsValidLocation(Location target_loc);

  std::map<bool, vector<Direction>> FilterDirection(std::vector<Direction> &poss_d, const Ghost &ghost);

  std::map<Direction, std::pair<int, int>> AddWeight(const std::map<bool, vector<Direction>>& poss_d);

  Direction PickWeightedDirection(const std::map<Direction, std::pair<int, int>>& directions);

 private:
  const size_t width;
  const size_t height;
  Map map;
  PacMan pacman;
  std::vector<Ghost> ghosts;
  std::mt19937 rng;
};

}

#endif  // FINALPROJECT_ENGINE_H
