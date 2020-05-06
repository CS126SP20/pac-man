// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <iostream>

#include <mylibrary/engine.h>
#include <mylibrary/food.h>
#include <mylibrary/food_type.h>
#include <mylibrary/ghost.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/location.h>
#include <mylibrary/map.h>
#include <mylibrary/pacman.h>
#include <mylibrary/player.h>

using myapp::Direction;
using myapp::Engine;
using myapp::Food;
using myapp::FoodType;
using myapp::Ghost;
using myapp::LeaderBoard;
using myapp::Location;
using myapp::Map;
using myapp::PacMan;
using myapp::Player;

/* ENGINE TESTS */
TEST_CASE("Engine Constructor, Getters and Setters, and Resets",
          "[engine][getter][setter][reset][reset_all][has_won]") {

  Engine standard_engine = Engine(36, 28);

  // This is true because Map is populated in my_app.cc. So as of now the map
  // is empty and thus HasWon() returns true.
  REQUIRE(standard_engine.HasWon() == true);

  SECTION("Getting PacMan and the Ghosts") {
    REQUIRE(standard_engine.GetPacMan().GetLocation() == Location(14, 20));

    REQUIRE(!standard_engine.GetGhosts().empty());
    REQUIRE(standard_engine.GetGhosts().size() == 4);
  }

  SECTION("Getting the score") {
    REQUIRE(standard_engine.GetScore() == 0);
  }

  SECTION("Setting direction of PacMan") {
    standard_engine.SetDirection(Direction::kRight);
    standard_engine.SetDirection(Direction::kLeft);

    REQUIRE(standard_engine.GetPacMan().GetDirection() == Direction::kLeft);
    REQUIRE(standard_engine.GetPacMan().GetLastDirection() == Direction::kRight);
  }

  SECTION("Setting and getting the boolean 'ate_special_food'") {
    REQUIRE(!standard_engine.GetAteSpecialFood());

    standard_engine.SetAteSpecialFood(true);
    REQUIRE(standard_engine.GetAteSpecialFood());
  }
}

/* FOOD TESTS */
TEST_CASE("Food Constructor and Getter",
          "[food][food_type][constructor][getter]") {

  Location loc = Location(0, 0);
  FoodType type = myapp::FoodType::kNormal;

  Food normal_food = Food(loc, type);

  REQUIRE(normal_food.GetLocation() == loc);
  REQUIRE(normal_food.GetFoodType() == type);
}

/* GHOST TESTS */
TEST_CASE("Ghost Constructor, Getters, and Setters",
          "[ghost][constructor][getter][setter]") {

  Location loc = Location(0, 0);
  Ghost ghost = Ghost(loc);

  REQUIRE(ghost.GetLocation() == loc);

  SECTION("Setting and getting location") {
    Location far_away_loc = Location(10000, 10000);
    ghost.SetLocation(far_away_loc);

    REQUIRE(ghost.GetLocation() == far_away_loc);

    Location negative_loc = Location(-1, -1);
    ghost.SetLocation(negative_loc);

    REQUIRE(ghost.GetLocation() == negative_loc);
  }

  SECTION("Setting and getting direction") {
    ghost.SetDirection(Direction::kRight);
    REQUIRE(ghost.GetDirection() == Direction::kRight);

    ghost.SetDirection(Direction::kDown);
    REQUIRE(ghost.GetDirection() == Direction::kDown);
  }

  SECTION("Setting and getting boolean 'in box'") {
    ghost.SetInBox(false);
    REQUIRE(!ghost.GetInBox());

    ghost.SetInBox(true);
    REQUIRE(ghost.GetInBox());
  }
}

/* LEADERBOARD TESTS */
// For some reason, this test does not pass.
TEST_CASE("Leaderboard Constructor, Retrieve High Scores, and Adding Scores",
          "[leaderboard][player][constructor][retrieve_scores][add_scores]") {

  LeaderBoard board = LeaderBoard("pacman.db");

  SECTION("Adding new players and scores") {
    Player first = Player("brianna", 9850);
    Player second = Player("brianna", 7120);
    Player third = Player("brianna", 6870);

    board.AddScoreToLeaderBoard(first);
    board.AddScoreToLeaderBoard(second);
    board.AddScoreToLeaderBoard(third);

    SECTION("Retrieving top players") {
      std::vector<Player> top_players = board.RetrieveHighScores(3);

      REQUIRE(top_players.at(0).name == first.name);
      REQUIRE(top_players.at(0).score == first.score);

      REQUIRE(top_players.at(1).name == second.name);
      REQUIRE(top_players.at(1).score == second.score);

      REQUIRE(top_players.at(2).name == third.name);
      REQUIRE(top_players.at(2).score == third.score);

      REQUIRE(!top_players.empty());
    }
  }
}

/* LOCATION TESTS */
TEST_CASE("Location Constructor and Accessors", "[location][constructor][accessor]") {
  int row = 15;
  int col = 3;
  Location loc = Location(row, col);

  REQUIRE(loc.Row() == row);
  REQUIRE(loc.Col() == col);
}

TEST_CASE("Location Comparison Operators", "[location][comparison_operators]") {
  Location one = Location(9, 7);
  Location two = Location(9, 7);

  Location three = Location(11, 11);
  Location four = Location(11, 2);
  Location five = Location(2, 11);
  Location six = Location(2, 2);

  SECTION("Equal to, not equal to") {
    REQUIRE(one == two);
    REQUIRE(!(one == three));

    REQUIRE(one != three);
    REQUIRE(!(one != two));
  }

  SECTION("Less than, less than or equal to") {
    REQUIRE(one < three);
    REQUIRE(one < four);
    REQUIRE(!(one < two));
    REQUIRE(!(one < six));
    REQUIRE(!(one < five));

    REQUIRE(one <= two);
    REQUIRE(one <= three);
    REQUIRE(one <= four);
    REQUIRE(!(one <= six));
    REQUIRE(!(one <= five));
  }

  SECTION("Greater than, greater than or equal to") {
    REQUIRE(one > six);
    REQUIRE(one > five);
    REQUIRE(!(one > two));
    REQUIRE(!(one > three));
    REQUIRE(!(one > four));

    REQUIRE(one >= two);
    REQUIRE(one >= five);
    REQUIRE(one >= six);
    REQUIRE(!(one >= three));
    REQUIRE(!(one >= four));
  }
}

TEST_CASE("Location Vector Operators", "[location][vector_operators]") {

  Location loc = Location(3, 9);

  SECTION("Plus") {
    Location southeast = Location(1, 1);
    REQUIRE(loc + southeast == Location(4, 10));

    Location northwest = Location(-1, -1);
    REQUIRE(loc + northwest == Location(2, 8));
  }

  SECTION("Subtraction") {
    Location southeast = Location(1, 1);
    REQUIRE(loc - southeast == Location(2, 8));

    Location northwest = Location(-1, -1);
    REQUIRE(loc - northwest == Location(4, 10));
  }

  SECTION("Inverse") {
    REQUIRE(-loc == Location(-3, -9));
    REQUIRE(-(-loc) == Location(3, 9));
  }

  SECTION("Plus equals") {
    loc += Location(1, 1);
    REQUIRE(loc == Location(4, 10));

    loc += Location(-5, -3);
    REQUIRE(loc == Location(-1, 7));
  }

  SECTION("Modulo positive") {
    Location loc1{12, 9};
    Location loc2{7, 3};

    Location result = loc1 % loc2;
    REQUIRE(result == Location{5, 0});
  }

  SECTION("Modulo positive") {
    Location loc1{-1, 3};
    Location loc2{7, 2};

    Location result = loc1 % loc2;
    REQUIRE(result == Location{6, 1});
  }
}

TEST_CASE("Location Output Stream Operator", "[location][output_operator]") {
  Location loc_one = Location(3, 3);
  Location loc_two = Location(1, 999);
  Location loc_three = Location(999, 2);

  std::cout << loc_one << std::endl;
  std::cout << loc_two << std::endl;
  std::cout << loc_three << std::endl;
}

/* MAP TESTS */
TEST_CASE("Map Getters and Setters", "[map][food][constructor][getter][setter]") {

  Map map = Map();

  SECTION("Setting and getting food") {
    std::vector<Food> map_food = { Food(Location(6, 0), FoodType::kNormal),
                                   Food(Location(21, 0), FoodType::kNormal),
                                   Food(Location(1, 1), FoodType::kSpecial),
                                   Food(Location(12, 2), FoodType::kCherry)};

    map.SetFood(map_food);

    REQUIRE(!map.GetFood().empty());

    for (int i = 0; i < map.GetFood().size(); i++) {
      REQUIRE(map.GetFood().at(i).GetLocation() == map_food.at(i).GetLocation());
      REQUIRE(map.GetFood().at(i).GetFoodType() == map_food.at(i).GetFoodType());
    }
  }

  SECTION("Setting and getting layout") {
    std::vector<char> line_one = { '#', '?', '-', 'o', '-', '&' };
    std::vector<char> line_two = { '.', '-', '?', 'c', '.', '#' };
    std::vector<std::vector<char>> layout = { line_one, line_two };

    map.SetLayout(layout);

    REQUIRE(!map.GetLayout().empty());

    for (int i = 0; i < map.GetLayout().size(); i++) {
      for (int j = 0; j < map.GetLayout().at(0).size(); j++) {
        REQUIRE(map.GetLayout()[i][j] == layout[i][j]);
      }
    }
  }
}

/* PACMAN TESTS */
TEST_CASE("PacMan Constructor, Getters, and Setters",
          "[pacman][constructor][getter][setter]") {

  Location loc = Location(0, 0);
  PacMan pac_man = PacMan(loc);

  REQUIRE(pac_man.GetLocation() == loc);

  SECTION("Setting and getting location") {
    Location far_away_loc = Location(10000, 10000);
    pac_man.SetLocation(far_away_loc);

    REQUIRE(pac_man.GetLocation() == far_away_loc);

    Location negative_loc = Location(-1, -1);
    pac_man.SetLocation(negative_loc);

    REQUIRE(pac_man.GetLocation() == negative_loc);
  }

  SECTION("Setting and getting direction") {
    pac_man.SetDirection(Direction::kDown);
    REQUIRE(pac_man.GetDirection() == Direction::kDown);

    pac_man.SetDirection(Direction::kRight);
    REQUIRE(pac_man.GetDirection() == Direction::kRight);
  }

  SECTION("Setting and getting last direction") {
    pac_man.SetLastDirection(Direction::kUp);
    REQUIRE(pac_man.GetLastDirection() == Direction::kUp);

    pac_man.SetLastDirection(Direction::kLeft);
    REQUIRE(pac_man.GetLastDirection() == Direction::kLeft);
  }

  SECTION("Setting and getting lives") {
    pac_man.SetLives(-3);
    REQUIRE(pac_man.GetLives() == -3);

    pac_man.SetLives(0);
    REQUIRE(pac_man.GetLives() == 0);

    pac_man.SetLives(10000);
    REQUIRE(pac_man.GetLives() == 10000);
  }
}