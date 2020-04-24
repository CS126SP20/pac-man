// Copyright (c) 2020 [Brianna Zhang]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using myapp::Direction;
using myapp::Location;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::vector;

const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";

DECLARE_uint32(width);
DECLARE_uint32(height);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_string(map_file);

MyApp::MyApp()
    : engine{FLAGS_width, FLAGS_height},
      map{},
      tile_size(FLAGS_tilesize),
      game_started{false} {}

void MyApp::setup() {
  pac_man_image = cinder::gl::Texture::create(loadImage(
      loadAsset("primitive-pac-man.png")));

  ghost_images.push_back(cinder::gl::Texture::create(loadImage(
      loadAsset("inky.png"))));

  ghost_images.push_back(cinder::gl::Texture::create(loadImage(
      loadAsset("blinky.png"))));

  ghost_images.push_back(cinder::gl::Texture::create(loadImage(
      loadAsset("pinky.png"))));

  ghost_images.push_back(cinder::gl::Texture::create(loadImage(
      loadAsset("clyde.png"))));

  gate_image = cinder::gl::Texture::create(loadImage(
          loadAsset("cyan_gate_block.png")));

  wall_image = cinder::gl::Texture::create(loadImage(
      loadAsset("blue_wall_block.png")));

  map.ParseFile(FLAGS_map_file);
  engine.SetMap(map);

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
  DrawBackground();

  DrawPacMan();
  DrawGhosts();

  /*
  if (!game_started) {
    DrawPreGame();
  }*/
}

void PrintText(const string& text, const Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kDifferentFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawBackground() const {
  vector<vector<char>> layout = map.GetLayout();

  for (int i = 3; i < FLAGS_height - 1; i++) {
    for (int j = 0; j < FLAGS_width; j++) {
      char c = layout[i][j];
      Location loc(j, i);

      if (c == '#') {
        cinder::gl::draw(wall_image,Rectf(tile_size * loc.Row(),
                                        tile_size * loc.Col(),
                                        tile_size * loc.Row() + tile_size,
                                        tile_size * loc.Col() + tile_size));

      } else if (c == '&') {
        cinder::gl::draw(gate_image, Rectf(tile_size * loc.Row(),
                                          tile_size * loc.Col(),
                                          tile_size * loc.Row() + tile_size,
                                          tile_size * loc.Col() + tile_size));
      }
    }
  }
}

void MyApp::DrawPreGame() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();
  const Location loc((FLAGS_width / 2) * tile_size, (FLAGS_height / 2) * tile_size);

  //PrintText("Press SPACE to begin", color, size, loc);
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

void MyApp::DrawGhosts() const {
  vector<Ghost> ghosts = engine.GetGhosts();

  for (int i = 0; i < 4; i++) {
    const Location loc = ghosts.at(i).GetLocation();

    cinder::gl::draw(ghost_images.at(i),
                     Rectf(tile_size * loc.Row(),
                           tile_size * loc.Col(),
                           tile_size * loc.Row() + tile_size,
                           tile_size * loc.Col() + tile_size));
    const cinder::vec2 center = getWindowCenter();
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine.SetPMDirection(Direction::kLeft);
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine.SetPMDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine.SetPMDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine.SetPMDirection(Direction::kDown);
      break;
    }
  }
}

}  // namespace myapp
