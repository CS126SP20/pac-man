//
// Created by Brianna Zhang on 4/21/20.
//

#ifndef FINALPROJECT_FILEMANAGER_H
#define FINALPROJECT_FILEMANAGER_H

#include <string>

namespace myapp {

class FileManager {
 public:
  bool IsValidFile(const std::string& file);

  std::vector<std::vector<char>> ParseFile(const std::string& file);

};
} // namespace myapp





#endif  // FINALPROJECT_FILEMANAGER_H
