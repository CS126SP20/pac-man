//
// Created by Brianna Zhang on 4/21/20.
//

#include "mylibrary/filemanager.h"
#include "mylibrary/map.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace myapp {

using std::string;
using std::vector;

bool FileManager::IsValidFile(const string& file) {
  std::ifstream infile(file);
  string line;

  while (getline(infile, line)) {
    for (int i = 0; i < line.length(); i++) {
      if (line.at(i) != '#' || line.at(i) != '-' || line.at(i) != '?'
          || line.at(i) != '&') {
        return false;
      }
    }
  }
  return true;
}

vector<vector<char>> FileManager::ParseFile(const string& file) {
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
  return map;
}

};


