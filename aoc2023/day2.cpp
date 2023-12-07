#include <iostream>
#include <vector>
#include <fstream>

typedef struct
{
    int id;
	int red;
    int blue;
    int green;
} round;

void print_round(const round& r)
{
    std::cout << "Round " << r.id
    << " r: " << r.red
    << " b: " << r.blue
    << " g: " << r.green
    << std::endl;
};

std::vector<std::vector<round>> test_input = {
    {{1, 4, 3, 0}, {1, 1, 6, 2}, {1, 0, 0, 2}},
    {{2, 0, 1, 2}, {2, 1, 4, 3}, {2, 0, 1, 1}},
    {{3, 20, 6, 8}, {3, 4, 5, 13}, {3, 1, 0, 5}},
    {{4, 3, 6, 1}, {4, 6, 0, 3}, {4, 14, 15, 3}},
    {{5, 6, 1, 3}, {5, 1, 2, 2}},
};

void print_games(const std::vector<std::vector<round>>& g)
{
    for ( size_t i=0; i<g.size(); i++ )
    {
        std::cout << "Game " << i+1 << ": ";
        for ( const round& r: g.at(i) )
        {
            std::cout << r.red << " red ";
            std::cout << r.blue << " blue ";
            std::cout << r.green << " green; ";
        }
        std::cout << std::endl;
    }
};

//Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
//Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
//Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
//Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
//Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

std::vector<round> parse_line(std::string& l)
{
    std::vector<round> g;
    //std::string l = "Game 21: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    size_t pos = 5;
    std::string game = l.substr(pos, l.find(':')-pos);
    pos += game.size() + 2;

    bool end_of_line = false;
    while ( !end_of_line )
    {
        size_t d = l.find(';', pos);
        if ( d == std::string::npos )
        {
            end_of_line =  true;
            d = l.size();
        }
        std::string round_str = l.substr(pos, d - pos);
        pos += round_str.size() + 2;

        bool ie = false;
        size_t ip = 0;
        while ( !ie )
        {
            size_t id = round_str.find(',', ip);
            round r = {stoi(game), 0, 0, 0};;
            while( id != std::string::npos )
            {
                std::string dice = round_str.substr(ip, id - ip);
                ip += dice.size() + 2;
                id = round_str.find(',', ip);
                if (dice.find("blue") != std::string::npos)
                {
                    r.blue = std::stoi(dice);
                }
                else if (dice.find("green") != std::string::npos)
                {
                    r.green = std::stoi(dice);
                }
                else if (dice.find("red") != std::string::npos)
                {
                    r.red = std::stoi(dice);
                }
            }
            std::string dice = round_str.substr(ip, id - ip);
			if (dice.find("blue") != std::string::npos)
			{
				r.blue = std::stoi(dice);
			}
			else if (dice.find("green") != std::string::npos)
			{
				r.green = std::stoi(dice);
			}
			else if (dice.find("red") != std::string::npos)
			{
				r.red = std::stoi(dice);
			}
            g.push_back(r);
            ip += dice.size() + 2;
            ie = true;
        }
    }
    return g;
}

int main()
{
    std::vector<std::vector<round>> input;
    std::ifstream instream("inputs/day2");
    for (std::string line; getline(instream, line);)
    {
        input.push_back(parse_line(line));
    }
    //parse_line();
    //return 0;
    int max_red = 12;
    int max_green = 13;
    int max_blue = 14;

    int res = 0;

    for ( size_t game=0; game<input.size(); game++)
    {
        int mr = 0;
        int mg = 0;
        int mb = 0;
        bool valid = true;
        for ( const round& r: input.at(game) )
        {
            mr = std::max(mr, r.red);
            mg = std::max(mg, r.green);
            mb = std::max(mb, r.blue);
            //if ( !(r.red <= max_red && r.green <= max_green && r.blue <= max_blue) )
            //{
            //    valid = false;
            //}
        }
        //if ( valid )
        //{
        res += (mr * mg * mb);
        //}
    }

    std::cout << res << std::endl;
    return 0;
};
