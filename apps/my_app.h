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

// Represents the index of each image in the pacman_images vector
const int kPacManRightImage = 0;
const int kPacManDownImage = 1;
const int kPacManLeftImage = 2;
const int kPacManUpImage = 3;

enum class GameState {
  kPreGame,         // Home screen
  kNewGame,         // Screen before the start of a new game
  kGameReset,       // Screen before continuing a game after PacMan hits a ghost
  kPlaying,         // Playing screen
  kPlayingSpecial,  // Playing screen when PacMan has eaten 'special' food
  kGameOver,        // Game over / leaderboard screen
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  // Draws the background
  void DrawBackground() const;

  /* == DRAWING THE DIFFERENT SCREENS == */
  // Draws the home screen
  void DrawPreGame() const;

  // Draws the screen before starting a new game. Says "Hit -ENTER- to begin"
  void DrawNewGame() const;

  // Draws the screen after PacMan hits a ghost. Says "Hit -ENTER- to continue"
  void DrawGameReset() const;

  // Draws the game over / leaderboard screen
  void DrawGameOver() const;

  /* == DRAWING ELEMENTS OF THE GAME == */
  void DrawPacMan() const;
  void DrawGhosts() const;
  void DrawFood() const;
  void DrawPoints() const;
  void DrawLives() const;

  /* == METHODS HANDLING THE AUDIO == */
  void BackgroundMusic() const;
  void EatingAudio() const;
  void DyingAudio() const;

  /* == SET-UP METHODS FOR IMAGES & AUDIO == */
  void SetUpImages();
  void SetUpAudio();

  // Returns a boolean representing whether or not the ghosts are in the
  // starting box.
  bool GhostsInBox() const;

 private:
  myapp::Engine engine;
  myapp::LeaderBoard leaderboard;
  const std::string player_name;
  GameState state;
  const size_t tile_size;
  std::vector<myapp::Player> top_players;
  std::chrono::time_point<std::chrono::system_clock> last_time;
  std::chrono::time_point<std::chrono::system_clock> last_time_special;

  /* == IMAGES == */
  cinder::gl::Texture2dRef title_image;
  cinder::gl::Texture2dRef title_decor;

  cinder::gl::Texture2dRef game_over;

  std::vector<cinder::gl::Texture2dRef> pacman_images;
  std::vector<cinder::gl::Texture2dRef> ghost_images;
  cinder::gl::Texture2dRef special_ghost;
  cinder::gl::Texture2dRef gate_image;
  cinder::gl::Texture2dRef wall_image;
  cinder::gl::Texture2dRef pm_life_image;
  cinder::gl::Texture2dRef cherry_image;

  /* == AUDIO FILES (.WAV) == */
  cinder::audio::VoiceRef background_music;
  cinder::audio::VoiceRef eating;
  cinder::audio::VoiceRef eating_special;
  cinder::audio::VoiceRef pacman_dying;
};
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
