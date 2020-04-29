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

void Map::SetFoodLoc(const vector<Location> &given_food_loc) {
  food_loc = given_food_loc;
}

vector<Location> Map::GetFoodLoc() const { return food_loc; }

void Map::ParseFile(const string& file) {
  vector<vector<char>> map;
  vector<Location> food_loc_temp;

  std::ifstream infile(file);
  string line;

  int row_count = 0;
  while (getline(infile, line)) {
    vector<char> layout_line;

    for (int i = 0; i < line.length(); i++) {
      char c = line.at(i);
      layout_line.push_back(static_cast<char>(c));

      if (c == '.') {
        Location loc = Location(i, row_count);
        food_loc_temp.push_back(loc);

      }
    }
    map.push_back(layout_line);
    row_count++;
  }
  SetLayout(map);
  SetFoodLoc(food_loc_temp);
}

}; // namespace myapp

