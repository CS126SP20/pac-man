// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <gflags/gflags.h>

#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/location.h>
#include <mylibrary/map.h>
#include <mylibrary/player.h>

namespace myapp {

enum class GameState {
  kPreGame,
  kNewGame,
  kGameReset,
  kPlaying,
  kPlayingSpecial,
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
  void DrawNewGame() const;
  void DrawGameReset() const;
  void DrawGameOver() const;

  void DrawPacMan() const;
  void DrawGhosts() const;
  void DrawFood() const;
  void DrawPoints() const;
  void DrawLives() const;

  void BackgroundMusic() const;

  bool GhostsInBox() const;

  // Occurs when Pac-Man loses a life:
  // Pac-Man starts at the same spot and ghosts start in the box, but nothing
  // else resets
  void Reset();

 private:
  myapp::Engine engine;
  myapp::LeaderBoard leaderboard;
  const std::string player_name;
  GameState state;
  const size_t tile_size;
  std::vector<myapp::Player> top_players;

  std::chrono::time_point<std::chrono::system_clock> last_time;
  std::chrono::time_point<std::chrono::system_clock> last_time_special;

  cinder::gl::Texture2dRef title_image;
  cinder::gl::Texture2dRef title_decor;

  cinder::gl::Texture2dRef game_over;

  cinder::gl::Texture2dRef pac_man_image;
  std::vector<cinder::gl::Texture2dRef> ghost_images;
  cinder::gl::Texture2dRef special_ghost;
  cinder::gl::Texture2dRef gate_image;
  cinder::gl::Texture2dRef wall_image;
  cinder::gl::Texture2dRef pm_life_image;
  cinder::gl::Texture2dRef cherry_image;

  cinder::audio::VoiceRef background_music;
  cinder::audio::VoiceRef eating_fruit;
  cinder::audio::VoiceRef eating_ghost;
  cinder::audio::VoiceRef eating_standard;
  cinder::audio::VoiceRef pacman_dying;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
