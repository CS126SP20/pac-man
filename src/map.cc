//
// Created by Brianna Zhang on 4/21/20.
//

#include "mylibrary/map.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace myapp {

using std::string;
using std::vector;

Map::Map() : layout(kMapHeight_int, vector<char>(kMapWidth_int, ' ')) {}

void Map::SetLayout(const vector<vector<char>>& given_layout) {
  layout = given_layout;
}

vector<vector<char>> Map::GetLayout() const { return layout; }

void Map::SetFood(const vector<Food> &given_food) {
  food = given_food;
}

vector<Food> Map::GetFood() const { return food; }

void Map::ParseFile(const string& file) {
  vector<vector<char>> map;
  vector<Food> food_temp;

  std::ifstream infile(file);
  string line;

  int row_count = 0;
  while (getline(infile, line)) {
    vector<char> layout_line;

    for (int i = 0; i < line.length(); i++) {
      char c = line.at(i);
      layout_line.push_back(static_cast<char>(c));

      Location loc = Location(i, row_count);

      if (c == '.') {
        Food f = Food(loc, FoodType::kNormal);
        food_temp.push_back(f);

      } else if (c == 'o') {
        Food f = Food(loc, FoodType::kSpecial);
        food_temp.push_back(f);

      } else if (c == 'c') {
        Food f = Food(loc, FoodType::kCherry);
        food_temp.push_back(f);
      }
    }
    map.push_back(layout_line);
    row_count++;
  }
  SetLayout(map);
  SetFood(food_temp);
}

void Map::ResetFood(const string &file) {
  vector<Food> food_temp;
  std::ifstream infile(file);
  string line;

  int row_count = 0;
  while (getline(infile, line)) {

    for (int i = 0; i < line.length(); i++) {
      char c = line.at(i);
      Location loc = Location(i, row_count);

      if (c == '.') {
        Food f = Food(loc, FoodType::kNormal);
        food_temp.push_back(f);

      } else if (c == 'o') {
        Food f = Food(loc, FoodType::kSpecial);
        food_temp.push_back(f);

      } else if (c == 'c') {
        Food f = Food(loc, FoodType::kCherry);
        food_temp.push_back(f);
      }
    }
    row_count++;
  }
  SetFood(food_temp);
}

}; // namespace myapp

