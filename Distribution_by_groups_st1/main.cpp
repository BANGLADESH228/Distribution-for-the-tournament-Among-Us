#include <iostream>
#include <vector>
#include <string>
#include <QRandomGenerator64>
#include <algorithm>

class Player {
public:
    std::string name;
    int result_of_player;

    std::vector<Player> players = {};
};

template<typename T>
void print(std::vector<T> const &v)
{
    for (auto &i: v) {
        std::cout << i << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    std::string name;
    int result, num_of_peoples = 0, num_of_groups = 0, num_of_team_members = 0;
    std::vector<int> results = {};

    std::string names[30] = {
        "Anatoliy", "Katya",   "Masha",     "Eva",      "Zema",  "Slavik",    "Margo",  "Yri",      "Vladimir", "Evilina",
        "Alesha",   "Vasiliy", "Dima",      "Ruslan",   "Oleg",  "Mikhail",   "Igor",   "Ivan",     "Gleb",     "Denis",
        "Alina",    "Alisa",   "Anastasia", "Viktoria", "Darya", "Ekaterina", "Kamila", "Kristina", "Ksenia",   "Natalya",
    };
    name = names[rand() % 30];

    std::cout << "Enter a number - the number of participants: ";
    std::cin >> num_of_peoples;
    std::cout << "Enter a number - the number of groups: ";
    std::cin >> num_of_groups;
    num_of_team_members = num_of_peoples / num_of_groups;

    for (int i = 0; i < num_of_peoples; ++i) {
        std::uniform_int_distribution<int> distribution(0, 10);
        result = distribution(*QRandomGenerator::global());
        results.push_back(result);
        std::sort(results.begin(), results.end());
    }

    if (num_of_peoples % num_of_groups == 0) {
        std::cout << "Result: ";
        for (auto const& r : results)
            std::cout << r << ' ';
    }

    std::cout << std::endl;

    int size = (results.size() - 1) / num_of_team_members + 1;
    std::vector<int> vec[size];

    for (int k = 0; k < size; ++k)
    {
        auto start_itr = std::next(results.cbegin(), k * num_of_team_members);
        auto end_itr = std::next(results.cbegin(), k * num_of_team_members + num_of_team_members);

        vec[k].resize(num_of_team_members);

        if (k * num_of_team_members + num_of_team_members > results.size())
        {
            end_itr = results.cend();
            vec[k].resize(results.size() - k * num_of_team_members);
        }

        std::copy(start_itr, end_itr, vec[k].begin());
    }

    for (int i = 0; i < size; i++) {
        print(vec[i]);
    }

    return 0;
}
