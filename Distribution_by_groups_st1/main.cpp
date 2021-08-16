#include "player.h"
#include <QRandomGenerator64>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <typename T1, typename T2>
void getRandomNumbers(T1 num, std::vector<T2> &vec) {
  for (int i = 0; i < num; ++i) {
    std::uniform_int_distribution<int> distribution(0, 10);
    int rez = distribution(*QRandomGenerator::global());
    vec.push_back(rez);
    std::sort(vec.begin(), vec.end());
  }
}

std::string getRandomName(std::string name) {
  std::string names[30] = {
      "Anatoliy", "Katya",     "Masha",    "Eva",      "Zema",      "Slavik",
      "Margo",    "Yri",       "Vladimir", "Evilina",  "Alesha",    "Vasiliy",
      "Dima",     "Ruslan",    "Oleg",     "Mikhail",  "Igor",      "Ivan",
      "Gleb",     "Denis",     "Alina",    "Alisa",    "Anastasia", "Viktoria",
      "Darya",    "Ekaterina", "Kamila",   "Kristina", "Ksenia",    "Natalya",
  };
  name = names[rand() % 30];

  return name;
}

double convertToPercentage(int percentage) {
  return static_cast<double>(percentage / 100.0);
}

std::ostream &operator<<(std::ostream &os, const Player &pl) {
  os << pl.name_ << ' ';
  return os;
}

template <typename T> void printVectors(std::vector<T> const &v) {
  for (auto &i : v)
    std::cout << i << ' ';

  std::cout << std::endl;
}

template <typename T>
void splitOriginalVector(int nGroups, int nMembers, std::vector<T> &results) {
  std::vector<Player> newVectors[nGroups];

  for (int i = 0; i < nGroups; ++i) {
    auto begin = std::next(results.cbegin(), i * nMembers);
    auto end = std::next(results.cbegin(), i * nMembers + nMembers);

    newVectors[i].resize(nMembers);
    std::copy(begin, end, newVectors[i].begin());
  }

  for (int i = 0; i < nGroups; ++i) {
    std::cout << "Team " << i + 1 << ": ";
    printVectors(newVectors[i]);
  }
}

int main() {
  int nPeoples = 0, nGroups = 0, nMembers = 0, nScores = 0, percentage = 0;

  std::vector<int> results = {}, scores = {};
  std::vector<Player> players, playersReady;
  std::string name = "", nickName = "";

  std::cout << "Enter a number - the number of participants: ";
  std::cin >> nPeoples;
  std::cout << "Enter a number - the number of groups: ";
  std::cin >> nGroups;
  std::cout << "Enter a number - the percentage: ";
  std::cin >> percentage;
  std::cout << "Enter a number - the number of scores: ";
  std::cin >> nScores;

  std::cout << std::endl;
  nMembers = nPeoples / nGroups;
  double newPercentage = convertToPercentage(percentage);

  for (int i = 0; i < nPeoples; ++i) {
    getRandomNumbers(nScores, scores);
    nickName = getRandomName(name);
    Player player(nickName, scores);
    players.push_back(player);
    std::cout << '#' << i + 1 << ' ' << player;

    for (auto const &sc : scores)
      std::cout << sc << ' ';

    std::cout << std::endl;

    auto finalResult = player.computeTruncatedMean(scores, newPercentage);
    std::cout << "Final result: " << finalResult << std::endl;

    Player playerReady(nickName, finalResult);
    playersReady.push_back(playerReady);

    scores.clear();
    std::cout << std::endl;
  }

  //Нарушена инкапсуляция
  std::sort(playersReady.begin(), playersReady.end(),
            [](Player const &a, Player const &b) {
              return a.finalResult_ < b.finalResult_;
            });

  splitOriginalVector(nGroups, nMembers, playersReady);

  return 0;
}
