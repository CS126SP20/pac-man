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
#include <mylibrary/map.h>

namespace myapp {

enum class GameState {
  kPreGame,
  kPlaying,
  kGameOver,
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void DrawBackground() const;
  void DrawPreGame() const;
  void DrawPacMan() const;
  void DrawGhosts() const;
  void DrawFood() const;
  void DrawPoints() const;

 private:
  myapp::Engine engine;
  GameState state;
  const size_t tile_size;
  std::chrono::time_point<std::chrono::system_clock> last_time;

  cinder::gl::Texture2dRef pac_man_image;
  std::vector<cinder::gl::Texture2dRef> ghost_images;
  cinder::gl::Texture2dRef gate_image;
  cinder::gl::Texture2dRef wall_image;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
