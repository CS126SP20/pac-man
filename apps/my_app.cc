// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

using namespace myapp;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp()
    : engine{28, 36} {}

void MyApp::setup() {
  pac_man_image = cinder::gl::Texture::create(loadImage(loadAsset("primitive-pac-man.png")));

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();

  cinder::gl::clear();
  cinder::gl::draw(pac_man_image, getWindowBounds());

}

void MyApp::DrawPacMan() const {

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
