#include <iostream>
#include <fstream>
#include <map>

enum HAND
{
    ROCK,
    PAPER,
    SCISSORS
};

enum OUTCOME
{
    WIN,
    LOSE,
    DRAW
};

std::map<std::string, HAND> hands = {
    {"A", ROCK},
    {"B", PAPER},
    {"C", SCISSORS},
    {"X", ROCK},
    {"Y", PAPER},
    {"Z", SCISSORS}
};

std::map<std::string, OUTCOME> outcomes = {
    {"X", LOSE},
    {"Y", DRAW},
    {"Z", WIN}
};

std::map<HAND, HAND> handBeats = {
    {ROCK, SCISSORS},
    {PAPER, ROCK},
    {SCISSORS, PAPER}
};

std::map<HAND, HAND> handLoses = {
    {ROCK, PAPER},
    {PAPER, SCISSORS},
    {SCISSORS, ROCK}
};

std::map<HAND, int> handValue = {
    {ROCK, 1},
    {PAPER, 2},
    {SCISSORS, 3}
};


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

        total_score += handValue.at(my_hand);

        if(opp_hand == my_hand)
        {
            total_score += 3;
        }
        else
        {
            if (handBeats.at(my_hand) == opp_hand)
                total_score += 6;
        }
    }

    return total_score;
}

int part_b()
{
    std::ifstream instream("input.txt");
    int total_score = 0;
    for(std::string line; getline(instream, line);)
    {
        std::string delim = " ";
        std::string left = line.substr(0, line.find(delim));
        std::string right = line.substr(line.find(delim) + delim.length(), line.length());
        HAND opp_hand = hands.at(left);
        OUTCOME outcome = outcomes.at(right);
        HAND my_hand;

        switch(outcome)
        {
            case WIN:
                my_hand = handLoses.at(opp_hand);
                total_score += 6;
                break;
            case DRAW:
                my_hand = opp_hand;
                total_score += 3;
                break;
            case LOSE:
                my_hand = handBeats.at(opp_hand);
                break;
        }

        total_score += handValue.at(my_hand);

    }
    return total_score;
}

int main()
{
    std::cout << "Part a: " << part_a() << std::endl;
    std::cout << "Part b: " << part_b() << std::endl;
    return 0;
}
