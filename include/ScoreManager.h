#pragma once
#include "globals.h"
#include <fstream>
#include <ostream>
class ScoreManager {
public:
  static ScoreManager &getInstance() {
    static ScoreManager instance;
    return instance;
  }

  void addScore(int points) { score += points; }

  int getScore() const { return score; }

  void resetScore() { score = 0; }

  void save(std::ofstream &os) { os << score << "\n"; }

  void load(std::ifstream &is) { is >> score; }

private:
  ScoreManager() : score(0) {}
  ~ScoreManager() = default;

  ScoreManager(const ScoreManager &) = delete;
  ScoreManager &operator=(const ScoreManager &) = delete;

  int score;
};
