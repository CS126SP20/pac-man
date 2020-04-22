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

void Map::ParseFile(const string& file) {
  vector<vector<char>> map;

  std::ifstream infile(file);
  string line;

  while (getline(infile, line)) {
    vector<char> layout_line;
    for (char i : line) {
      layout_line.push_back(static_cast<char>(i));
    }

    map.push_back(layout_line);
  }
  SetLayout(map);
}

}; // namespace myapp

