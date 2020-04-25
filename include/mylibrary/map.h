//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include "location.h"

#include <string>
#include <vector>

namespace myapp {

constexpr size_t kMapWidth = 28;
constexpr int kMapWidth_int = static_cast<int>(kMapWidth);

constexpr size_t kMapHeight = 36;
constexpr int kMapHeight_int = static_cast<int>(kMapHeight);

using std::string;
using std::vector;

class Map {
 public:
  Map();

  void ParseFile(const string& file);

  void SetLayout(const vector<vector<char>>& given_layout);
  vector<vector<char>> GetLayout() const;

  void SetFoodLoc(const vector<Location>& given_food_loc);
  vector<Location> GetFoodLoc() const;

 private:
  vector<vector<char>> layout;
  vector<Location> food_loc;
};
}

#endif  // FINALPROJECT_MAP_H
