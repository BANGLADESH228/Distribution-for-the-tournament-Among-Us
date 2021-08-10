#include <iostream>
#include <vector>
#include <string>
#include <QRandomGenerator64>
#include <algorithm>

template<typename T>
void print_new_vectors(std::vector<T> const &v)
{
    for (auto &i: v)
        std::cout << i << ' ';

    std::cout << std::endl;
}

void generate_random_numbers(int num, std::vector<int>& vec)
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

void split_original_and_print_vec(int num_of_groups,
                        int num_of_team_members, std::vector<int>& results)
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

class Player
{
public:
    Player(){};

    Player(std::string name_, std::vector<int> scores_)
    {
       name = name_;
       scores = scores_;
    }

    double calculate_result(std::vector<int> scores,
                     double const percentage, int const num_of_scores)
    {
       generate_random_numbers(num_of_scores, scores);
       auto remove_count = static_cast<size_t>(scores.size() * percentage + 0.5);

       scores.erase(std::begin(scores), std::begin(scores) + remove_count);
       scores.erase(std::end(scores) - remove_count, std::end(scores));

       auto total = std::accumulate(std::cbegin(scores), std::cend(scores),
                                    0ull, [](auto const sum, auto const e){ sum += e; });

       return static_cast<double>(total) / scores.size();
    }

    ~Player(){};

private:
    std::string name;
    std::vector<int> scores;
};

int main()
{
    std::string name;
    int num_of_peoples = 0, num_of_groups = 0, num_of_team_members = 0, num_of_scores = 0;
    std::vector<int> results = {};
    std::vector<int> scores = {};
    double percentage = 0;

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

    generate_random_numbers(num_of_peoples, results);

    if (num_of_peoples % num_of_groups == 0)
    {
        std::cout << "Result: ";
        for (auto const& r : results)
            std::cout << r << ' ';
    }

    std::cout << std::endl;
    split_original_and_print_vec(num_of_groups, num_of_team_members, results);

    ////////////////////////////////////////////////////////////////////////////////////////


    std::cout << "Enter a number - the percentage: ";
    std::cin >> percentage;
    std::cout << "Enter a number - the number of scores: ";
    std::cin >> num_of_scores;

    Player player(name, scores);
    player.calculate_result(scores, percentage, num_of_scores);

    return 0;
}
