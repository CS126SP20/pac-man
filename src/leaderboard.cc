//
// Created by Brianna Zhang on 5/2/20.
//

#include "mylibrary/leaderboard.h"
#include "mylibrary/player.h"

#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace myapp {

using std::string;
using std::vector;

LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  try {
    db_ << "INSERT INTO leaderboard (name,score) VALUES (?,?);"
        << player.name
        << static_cast<int>(player.score);

  } catch (const std::exception& e) {
    std::cout << e.what() << " while adding score to leaderboard" << std::endl;
  }
}

vector<Player> GetPlayers(sqlite::database_binder* rows) {
  vector<Player> players;

  for (auto&& row : *rows) {
    string name;
    size_t score;
    row >> name >> score;
    Player player = {name, score};
    players.push_back(player);
  }

  return players;
}

vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  try {
    auto rows = db_ << "SELECT name,score FROM leaderboard ORDER BY score DESC "
                       "LIMIT ?;"
                    << limit;

    return GetPlayers(&rows);

  } catch (std::exception& e) {
    std::cout << e.what() << " while retrieving scores" << std::endl;
  }
}
}