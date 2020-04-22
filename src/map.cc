//
// Created by Brianna Zhang on 4/21/20.
//

#include "mylibrary/map.h"

#include <vector>

namespace myapp {

using std::vector;

Map::Map() : layout(kMapHeight_int, vector<char>(kMapWidth_int, ' ')) {}

void Map::SetLayout(const vector<vector<char>>& given_layout) {
  layout = given_layout;
}

vector<vector<char>> Map::GetLayout() { return vector<vector<char>>(); }

}; // namespace myapp

