#include "player.h"

Player::Player(){};

Player::Player(std::string name, std::vector<int> scores) {
  name_ = name;
  scores_ = scores;
}

Player::Player(std::string name, double finalResult) {
  name_ = name;
  finalResult_ = finalResult;
}

double Player::computeTruncatedMean(std::vector<int> scores,
                                    double const percentage) {
  auto removeCount = static_cast<size_t>(scores.size() * percentage + 0.5);
  scores.erase(std::begin(scores), std::begin(scores) + removeCount);
  scores.erase(std::end(scores) - removeCount, std::end(scores));

  auto total =
      std::accumulate(std::cbegin(scores), std::cend(scores), 0ull,
                      [](auto const sum, auto const e) { return sum + e; });

  return static_cast<double>(total) / scores.size();
}

Player::~Player(){};
