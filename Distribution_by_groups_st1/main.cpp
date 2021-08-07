#include <iostream>
#include <vector>
#include <string>
#include <QRandomGenerator64>
#include <algorithm>

//class Player
//{
//public:
//    std::string name;
//    int result_of_player;

//    std::vector<Player> players = {};
//};

template<typename T>
void print_new_vectors(std::vector<T> const &v)
{
    for (auto &i: v)
        std::cout << i << ' ';

    std::cout << std::endl;
}

void generate_random_members(int num, std::vector<int>& vec)
{
    int rez;

    for (int i = 0; i < num; ++i)
    {
        std::uniform_int_distribution<int> distribution(0, 10);
        rez = distribution(*QRandomGenerator::global());
        vec.push_back(rez);
        std::sort(vec.begin(), vec.end());
    }
}

void split_original_vec(int num_of_groups, int num_of_team_members, std::vector<int>& results)
{
    std::vector<int> new_vec[num_of_groups];

    for (int i = 0; i < num_of_groups; ++i)
    {
        auto start_itr = std::next(results.cbegin(), i * num_of_team_members);
        auto end_itr = std::next(results.cbegin(), i * num_of_team_members + num_of_team_members);
        new_vec[i].resize(num_of_team_members);
        std::copy(start_itr, end_itr, new_vec[i].begin());
    }

    for (int i = 0; i < num_of_groups; ++i)
    {
        std::cout << "Team " << i + 1 << ": ";
        print_new_vectors(new_vec[i]);
    }
}

int main()
{
    //std::string name;
    int num_of_peoples = 0, num_of_groups = 0, num_of_team_members = 0;
    std::vector<int> results = {};

//    std::string names[30] = {
//        "Anatoliy", "Katya",   "Masha",     "Eva",      "Zema",  "Slavik",    "Margo",  "Yri",      "Vladimir", "Evilina",
//        "Alesha",   "Vasiliy", "Dima",      "Ruslan",   "Oleg",  "Mikhail",   "Igor",   "Ivan",     "Gleb",     "Denis",
//        "Alina",    "Alisa",   "Anastasia", "Viktoria", "Darya", "Ekaterina", "Kamila", "Kristina", "Ksenia",   "Natalya",
//    };
//    name = names[rand() % 30];

    std::cout << "Enter a number - the number of participants: ";
    std::cin >> num_of_peoples;
    std::cout << "Enter a number - the number of groups: ";
    std::cin >> num_of_groups;

    num_of_team_members = num_of_peoples / num_of_groups;

    generate_random_members(num_of_peoples, results);

    if (num_of_peoples % num_of_groups == 0)
    {
        std::cout << "Result: ";
        for (auto const& r : results)
            std::cout << r << ' ';
    }

    std::cout << std::endl;
    split_original_vec(num_of_groups, num_of_team_members, results);

    return 0;
}
