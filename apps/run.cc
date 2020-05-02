// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>
#include <iostream>
#include <string>
#include <vector>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace myapp {

// (height, width)
// (x, y)
// ([0 - 28), [0 - 36))
// (col, row) for Location

DEFINE_uint32(width, 36, "the number of tiles in a row");
DEFINE_uint32(height, 28, "the number of rows");
DEFINE_uint32(tilesize, 20, "the size of each tile");
DEFINE_uint32(speed, 50, "the speed (delay) of the game");
DEFINE_string(name, "brianna", "the name of the player");

std::string file_name = "/Users/bzhang/Downloads/cinder_0.9.2_mac/my-projects/final-project-bzhang33/tests/data/standard_map";
DEFINE_string(map_file, file_name,"the file of the map");

const int kSamples = 8;

void ParseArgs(std::vector<std::string>* args) {
  gflags::SetUsageMessage(
      "Play a game of Pac-Man. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  std::vector<std::string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  const int width = static_cast<int>(FLAGS_width * FLAGS_tilesize);
  const int height = static_cast<int>(FLAGS_height * FLAGS_tilesize);

  settings->setWindowSize(height, width);
  settings->setResizable(false);
  settings->setTitle("My CS 126 Application");

  std::srand(std::time(0));
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
