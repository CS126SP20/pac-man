// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <iostream>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace myapp {

const int kSamples = 8;
const int kBoardWidth = 28; // Standard width of traditional Pac-Man board
const int kBoardHeight = 36; // Standard height of traditional Pac-Man board

const int kWidth = kBoardWidth * 22;
const int kHeight = kBoardHeight * 22;

void SetUp(App::Settings* settings, int argc, char** argv) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");

  std::string file = argv[1];
  std::ifstream infile(file);

  if (infile.fail()) {
    std::cerr << "Error: " << (std::error_code()) << std::endl;
  }



}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
