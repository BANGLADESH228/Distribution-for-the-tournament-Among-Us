#include <iostream>
#include <vector>
#include <string>
#include <QRandomGenerator64>
#include <algorithm>
#include <iterator>

template<typename T>
void print_new_vectors(std::vector<T> const &v)
{
    for (auto &i: v)
        std::cout << i << ' ';

    std::cout << std::endl;
}

void generate_random_numbers(int num, std::vector<int>& vec)
{
    for (int i = 0; i < num; ++i)
    {
        std::uniform_int_distribution<int> distribution(0, 10);
        int rez = distribution(*QRandomGenerator::global());
        vec.push_back(rez);
        std::sort(vec.begin(), vec.end());
    }
}

double to_percentage(int percentage)
{
    return static_cast<double>(percentage / 100.0);
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

    Player(std::string name_, double final_result_)
    {
        name = name_;
        final_result = final_result_;
    }

    double truncated_mean(std::vector<int> scores, double const percentage)
    {
       auto remove_count = static_cast<size_t>(scores.size() * percentage + 0.5);
       scores.erase(std::begin(scores), std::begin(scores) + remove_count);
       scores.erase(std::end(scores) - remove_count, std::end(scores));

       auto total = std::accumulate(std::cbegin(scores), std::cend(scores),
                                    0ull, [](auto const sum, auto const e){ return sum + e; });

       return static_cast<double>(total) / scores.size();
    }

    void sort_final_vec(std::vector<Player> players_ready)
    {
        std::sort(players_ready.begin(), players_ready.end(),
                  [](Player const &a, Player const &b) { return a.final_result < b.final_result; });
    }

    std::string get_name(std::string name)
    {
        return name;
    }

//    std::string get_results(std::vector<int> scores)
//    {
//        return scores;
//    }

    ~Player(){};

    friend std::ostream& operator<<(std::ostream& os, const Player& pl);
//    friend std::sort(players_ready.begin(), players_ready.end(), [](){});

private:
    std::string name;
    std::vector<int> scores;
    double final_result;
};

std::ostream& operator<<(std::ostream& os, const Player& pl)
{
    os << pl.name << ' ';
    return os;
}

//template <class T>
//std::ostream & operator << (std::ostream& os, const std::vector<T>& v)
//{
//    for (unsigned int i=0; i < v.size() ; i++)
//    {
//        if (i > 0)
//            os << ',';
//        os << v[i];
//    }

//    return os;
//}

void split_original_and_print_vec(int num_of_groups,
                        int num_of_team_members, std::vector<Player>& results)
{
    std::vector<Player> new_vec[num_of_groups];

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
    int num_of_peoples = 0, num_of_groups = 0,
            num_of_team_members = 0, num_of_scores = 0, percentage = 0;

    std::vector<int> results = {};
    std::vector<int> scores = {};
    std::vector<Player> players;
    std::vector<Player> players_ready;


    std::string names[30] = {
        "Anatoliy", "Katya",   "Masha",     "Eva",      "Zema",  "Slavik",    "Margo",  "Yri",      "Vladimir", "Evilina",
        "Alesha",   "Vasiliy", "Dima",      "Ruslan",   "Oleg",  "Mikhail",   "Igor",   "Ivan",     "Gleb",     "Denis",
        "Alina",    "Alisa",   "Anastasia", "Viktoria", "Darya", "Ekaterina", "Kamila", "Kristina", "Ksenia",   "Natalya",
    };
    std::string name;

    std::cout << "Enter a number - the number of participants: ";
    std::cin >> num_of_peoples;
    std::cout << "Enter a number - the number of groups: ";
    std::cin >> num_of_groups;

    num_of_team_members = num_of_peoples / num_of_groups;

    std::cout << std::endl;

    std::cout << "Enter a number - the percentage: ";
    std::cin >> percentage;
    std::cout << "Enter a number - the number of scores: ";
    std::cin >> num_of_scores;

    generate_random_numbers(num_of_scores, scores);
    double new_percentage = to_percentage(percentage);
    std::cout << "Percentage: " << new_percentage << std::endl;

    for (int i = 0; i < num_of_peoples; ++i)
    {
        generate_random_numbers(num_of_scores, scores);
        name = names[rand() % 30];
        Player player(name, scores);
        players.push_back(player);
        std::cout << player;

        for (auto const& sc : scores)
            std::cout << sc << ' ';

        std::cout << std::endl;

        auto final_result = player.truncated_mean(scores, new_percentage);

        std::cout << "Final: " << final_result << std::endl;

        Player player_ready(name, final_result);
        players_ready.push_back(player_ready);

        scores.clear();
        std::cout << std::endl;
    }

    std::cout << std::endl;
    //player_ready.sort_final_vec(players_ready);
    split_original_and_print_vec(num_of_groups, num_of_team_members, players_ready);

    return 0;
}
