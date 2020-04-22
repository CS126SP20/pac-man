// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <gflags/gflags.h>

#include <mylibrary/engine.h>
#include <mylibrary/direction.h>
#include <mylibrary/location.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawPacMan() const;

 private:
  myapp::Engine engine;
  cinder::gl::Texture2dRef pac_man_image;
  const size_t tile_size;
  std::chrono::time_point<std::chrono::system_clock> last_time;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
