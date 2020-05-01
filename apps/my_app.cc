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
      state{GameState::kPreGame},
      tile_size(FLAGS_tilesize) {}

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

  pm_life_image = cinder::gl::Texture::create(loadImage(
      loadAsset("pac_man_lives.png")));

  cherry_image = cinder::gl::Texture::create(loadImage(
      loadAsset("cherry.png")));

  Map map = Map();
  map.ParseFile(FLAGS_map_file);
  engine.SetMap(map);

  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  const auto time = system_clock::now();

  if (state == GameState::kPlaying) {
    // The constant is speed_; need to add GFLAGS later / make const variable
    if (time - last_time > std::chrono::milliseconds(50)) {
      if (engine.GetPacMan().GetLives() <= 0) {
        state = GameState::kGameOver;

      } else {
        engine.Step();
        last_time = time;
      }
    }
  }
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();

  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();

  cinder::gl::clear();

  if (state == GameState::kGameOver) {
    DrawGameOver();

  } else {
    if (state == GameState::kPreGame) {
      DrawPreGame();
    }
    DrawBackground();
    DrawFood();
    DrawLives();
    DrawPacMan();
    DrawGhosts();
    DrawPoints();
  }
}

void PrintText(const string& text, const Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
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
  vector<vector<char>> layout = engine.GetMap().GetLayout();

  for (int row = 3; row < FLAGS_width - 1; row++) {
    for (int col = 0; col < FLAGS_height; col++) {
      char c = layout[row][col];
      Location loc(col, row);

      if (c == '#') {
        // Draws the walls
        cinder::gl::draw(wall_image,Rectf(tile_size * loc.Row(),
                                        tile_size * loc.Col(),
                                        tile_size * loc.Row() + tile_size,
                                        tile_size * loc.Col() + tile_size));

      } else if (c == '&' && state != GameState::kPlaying) {
        // Draws the gates that let the ghosts out
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

  PrintText("Press 'ENTER' to begin", color, size,
            {(FLAGS_height / 2) * tile_size, (FLAGS_width / 18) * tile_size});
}

void MyApp::DrawGameOver() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  PrintText("GAME OVER", color, size,
            {(FLAGS_height / 2) * tile_size, (FLAGS_width / 2) * tile_size});
}

void MyApp::DrawPacMan() const {
  PacMan pacman = engine.GetPacMan();
  const Location loc = pacman.GetLocation();

  cinder::gl::draw(pac_man_image, Rectf(tile_size * loc.Row(),
                                        tile_size * loc.Col(),
                                        tile_size * loc.Row() + tile_size,
                                        tile_size * loc.Col() + tile_size));
}

void MyApp::DrawGhosts() const {
  vector<Ghost> ghosts = engine.GetGhosts();

  for (int i = 0; i < kNumGhosts; i++) {
    const Location loc = ghosts.at(i).GetLocation();

    cinder::gl::draw(ghost_images.at(i),
                     Rectf(tile_size * loc.Row(),
                           tile_size * loc.Col(),
                           tile_size * loc.Row() + tile_size,
                           tile_size * loc.Col() + tile_size));
  }
}

void MyApp::DrawFood() const {
  std::vector<Location> food_loc = engine.GetMap().GetFoodLoc();

  for (auto loc : food_loc) {
    const cinder::vec2 center = {(loc.Row() * tile_size) + (tile_size / 2),
                                 (loc.Col() * tile_size) + (tile_size / 2)};

    //cinder::gl::color(1, 0.8, 0.6);
    cinder::gl::drawSolidCircle(center, 2, -1);
  }

  Location loc = Location(5, 2);

  cinder::gl::draw(cherry_image, Rectf(tile_size * loc.Row(),
                                       tile_size * loc.Col(),
                                       tile_size * loc.Row() + tile_size,
                                       tile_size * loc.Col() + tile_size));
}

void MyApp::DrawPoints() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  std::string points_str = std::to_string(engine.GetPoints());

  PrintText(points_str, color, size,
            {(FLAGS_height) * (tile_size - 2), (FLAGS_width / 18) * tile_size});
}

void MyApp::DrawLives() const {
  int num_lives = engine.GetPacMan().GetLives();

  for (int i = 0; i < num_lives; i++) {
    Location loc = Location(1 + i, 1);
    cinder::gl::draw(pm_life_image,
                     Rectf(tile_size * (loc.Row()),
                           tile_size * loc.Col(),
                           tile_size * (loc.Row()) + tile_size,
                           tile_size * loc.Col() + tile_size));
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP: {
      engine.SetPMDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_DOWN:{
      engine.SetPMDirection(Direction::kDown);
      break;
    }
    case KeyEvent::KEY_LEFT:{
      engine.SetPMDirection(Direction::kLeft);
      break;
    }
    case KeyEvent::KEY_RIGHT:{
      engine.SetPMDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_RETURN:{
      state = GameState::kPlaying;
      break;
    }
  }
}

}  // namespace myapp
