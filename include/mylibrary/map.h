//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include "food.h"
#include "food.h"
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
  // Constructor
  Map();

  // Parses the file and populates Map layout and food vectors
  void ParseFile(const string& file);

  // Getter and setter for layout, a vector of vectors of chars
  vector<vector<char>> GetLayout() const;
  void SetLayout(const vector<vector<char>>& given_layout);

  // Getter and setter for food, a vector of Food objects
  vector<Food> GetFood() const;
  void SetFood(const vector<Food>& given_food);

 private:
  vector<vector<char>> layout;
  vector<Food> food;
};
}

#endif  // FINALPROJECT_MAP_H
