// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <iostream>
#include <string>
#include <vector>

#include "my_app.h"

using cinder::app::App;
using cinder::app::RendererGl;

namespace myapp {

const int kSamples = 8;
const int kBoardWidth = 28; // Standard width of traditional Pac-Man board
const int kBoardHeight = 36; // Standard height of traditional Pac-Man board

const int kWidth = kBoardWidth * 22;
const int kHeight = kBoardHeight * 22;

void ParseArgs(std::vector<std::string>* args) {
  int argc = static_cast<int>(args->size());

  std::vector<char*> argvs;
  for (std::string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  

}

void SetUp(App::Settings* settings) {
  std::vector<std::string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");


}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
