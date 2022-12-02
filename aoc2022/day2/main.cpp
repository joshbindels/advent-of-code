#include <iostream>
#include <fstream>
#include <map>

enum HAND
{
    ROCK,
    PAPER,
    SCISSORS
};

std::map<std::string, HAND> hands = {
    {"A", ROCK},
    {"B", PAPER},
    {"C", SCISSORS},
    {"X", ROCK},
    {"Y", PAPER},
    {"Z", SCISSORS}
};

bool left_won(HAND left, HAND right)
{
    if(left == ROCK && right == SCISSORS)return true;
    if(left == PAPER && right == ROCK) return true;
    if(left == SCISSORS && right == PAPER) return true;
    return false;
}

int part_a()
{
    std::ifstream instream("input.txt");
    int total_score = 0;
    for(std::string line; getline(instream, line);)
    {
        std::string delim = " ";
        std::string left = line.substr(0, line.find(delim));
        std::string right = line.substr(line.find(delim) + delim.length(), line.length());
        HAND opp_hand = hands.at(left);
        HAND my_hand = hands.at(right);
        switch(my_hand)
        {
            case ROCK:
                total_score += 1;
                break;
            case PAPER:
                total_score += 2;
                break;
            case SCISSORS:
                total_score += 3;
                break;
        }

        if(opp_hand == my_hand)
        {
            total_score += 3;
        }
        else
        {
            if(left_won(my_hand, opp_hand))
                total_score += 6;
        }
    }

    return total_score;
}

int main()
{
    std::cout << "Part a: " << part_a() << std::endl;
    return 0;
}
