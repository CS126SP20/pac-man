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

const char kDbPath[] = "pacman.db";

const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";

const int kLimit = 3;

DECLARE_uint32(width);
DECLARE_uint32(height);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_string(map_file);
DECLARE_string(name);

MyApp::MyApp()
    : engine{FLAGS_width, FLAGS_height},
      leaderboard{cinder::app::getAssetPath(kDbPath).string()},
      player_name{FLAGS_name},
      state{GameState::kNewGame},
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

  special_ghost = cinder::gl::Texture::create(loadImage(
      loadAsset("ghost_special.png")));

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

  if (state == GameState::kGameOver) {
    if (top_players.empty()) {
      leaderboard.AddScoreToLeaderBoard({player_name, engine.GetScore()});
      top_players = leaderboard.RetrieveHighScores(kLimit);
      assert(!top_players.empty());
    }
  }

  if (state == GameState::kPlaying || state == GameState::kPlayingSpecial) {
    if (time - last_time > std::chrono::milliseconds(65)) {
      if (engine.GetPacMan().GetLives() <= 0) {
        state = GameState::kGameOver;

      } else if (engine.GetHitGhost()) {
        engine.Reset();
        state = GameState::kGameReset;

      } else {
        engine.Step();
        last_time = time;
      }
    }

    // Reverts back to regular ghosts after 5 seconds
    if (time - last_time_special > std::chrono::seconds(20)
        && state == GameState::kPlayingSpecial) {
      state = GameState::kPlaying;
      engine.SetAteSpecialFood(false);
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
    if (state == GameState::kNewGame) {
      DrawNewGame();
    }

    if (state == GameState::kGameReset) {
      engine.Reset();
      DrawGameReset();
    }

    if (engine.GetAteSpecialFood() && state != GameState::kPlayingSpecial) {
      state = GameState::kPlayingSpecial;
      last_time_special = system_clock::now();
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

bool MyApp::GhostsInBox() const {
  std::vector<Ghost> ghosts = engine.GetGhosts();
  for (auto & ghost : ghosts) {
    if (ghost.GetInBox()) {
      return false;
    }
  }
  return true;
}

void MyApp::DrawBackground() const {
  vector<vector<char>> layout = engine.GetMap().GetLayout();

  for (int row = 3; row < FLAGS_width - 1; row++) {
    for (int col = 0; col < FLAGS_height; col++) {
      char c = layout[row][col];
      Location loc(col, row);

      bool are_ghosts_in_box = GhostsInBox();

      if (c == '#') {
        // Draws the walls
        cinder::gl::draw(wall_image,Rectf(tile_size * loc.Row(),
                                        tile_size * loc.Col(),
                                        tile_size * loc.Row() + tile_size,
                                        tile_size * loc.Col() + tile_size));

        // Draws the gates
      } else if (c == '&' && ((state == GameState::kNewGame) ||
                              (state != GameState::kNewGame &&
                               state != GameState::kPlayingSpecial &&
                               are_ghosts_in_box))) {

        cinder::gl::draw(gate_image, Rectf(tile_size * loc.Row(),
                                           tile_size * loc.Col(),
                                           tile_size * loc.Row() + tile_size,
                                           tile_size * loc.Col() + tile_size));
      }
    }
  }
}

void MyApp::DrawPreGame() const {

}

void MyApp::DrawNewGame() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  PrintText("Press 'ENTER' to begin", color, size,
            {(FLAGS_height / 2) * tile_size, (FLAGS_width / 18) * tile_size});
}

void MyApp::DrawGameReset() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  PrintText("Uh oh! Hit 'ENTER'", color, size,
            {(FLAGS_height / 2) * tile_size, (FLAGS_width / 18) * tile_size});
}

void MyApp::DrawGameOver() const {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  size_t row = 0;
  PrintText("GAME OVER", color, size, {getWindowHeight() / 2,
            getWindowHeight() / 10});

  PrintText("All Time Top:", color, size,
            {getWindowHeight() / 4, getWindowHeight() / 4});
  for (const myapp::Player& player : top_players) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {getWindowHeight() / 4,
                                      (getWindowHeight() / 4) + (++row) * 50});
  }
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

    if (state == GameState::kPlayingSpecial) {
      cinder::gl::draw(special_ghost,
                       Rectf(tile_size * loc.Row(),
                             tile_size * loc.Col(),
                             tile_size * loc.Row() + tile_size,
                             tile_size * loc.Col() + tile_size));
    } else {
      cinder::gl::draw(ghost_images.at(i),
                       Rectf(tile_size * loc.Row(),
                             tile_size * loc.Col(),
                             tile_size * loc.Row() + tile_size,
                             tile_size * loc.Col() + tile_size));
    }
  }
}

void MyApp::DrawFood() const {
  std::vector<Food> food = engine.GetMap().GetFood();

  for (auto & i : food) {
    FoodType type = i.GetFoodType();
    Location loc = i.GetLocation();
    const cinder::vec2 center = {(loc.Row() * tile_size) + (tile_size / 2),
                                 (loc.Col() * tile_size) + (tile_size / 2)};

    if (type == FoodType::kNormal) {
      cinder::gl::drawSolidCircle(center, 2, -1);

    } else if (type == FoodType::kSpecial) {
      cinder::gl::drawSolidCircle(center, 8, -1);

    } else if (type == FoodType::kCherry) {
      cinder::gl::draw(cherry_image, Rectf(tile_size * loc.Row(),
                                           tile_size * loc.Col(),
                                           tile_size * loc.Row() + tile_size,
                                           tile_size * loc.Col() + tile_size));
    }
  }
}

void MyApp::DrawPoints() const {
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  std::string points_str = std::to_string(engine.GetScore());

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
