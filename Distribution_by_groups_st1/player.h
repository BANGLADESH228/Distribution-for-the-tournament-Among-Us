#ifndef PLAYER_H
#define PLAYER_H

#include <QRandomGenerator64>
#include <iostream>
#include <numeric>
#include <vector>

class Player {
public:
  Player();
  double finalResult_;
  Player(std::string, std::vector<int>);
  Player(std::string, double);

  double computeTruncatedMean(std::vector<int>, double const);

  ~Player();

  friend std::ostream &operator<<(std::ostream &os, const Player &pl);

private:
  std::string name_;
  std::vector<int> scores_;
};

#endif // PLAYER_H
