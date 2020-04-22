// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Vector.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using myapp::Direction;
using myapp::Location;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

DECLARE_uint32(width);
DECLARE_uint32(height);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_string(map_file);

MyApp::MyApp()
    : engine{FLAGS_width, FLAGS_height},
      tile_size(FLAGS_tilesize) {}

void MyApp::setup() {
  pac_man_image = cinder::gl::Texture::create(
      loadImage(loadAsset("primitive-pac-man.png")));

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {

  const auto time = system_clock::now();

  // The constant is speed_; need to add GFLAGS later / make const variable
  if (time - last_time > std::chrono::milliseconds(50)) {
    engine.Step();
    last_time = time;
  }

}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();

  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();

  cinder::gl::clear();
  DrawPacMan();
}

void MyApp::DrawPacMan() const {
  PacMan pacman = engine.GetPacMan();
  const Location loc = pacman.GetLocation();

  cinder::gl::draw(pac_man_image, Rectf(tile_size * loc.Row(),
                                        tile_size * loc.Col(),
                                        tile_size * loc.Row() + tile_size,
                                        tile_size * loc.Col() + tile_size));
  const cinder::vec2 center = getWindowCenter();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine.SetDirection(Direction::kLeft);
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine.SetDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine.SetDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine.SetDirection(Direction::kDown);
      break;
    }
  }
}

}  // namespace myapp
