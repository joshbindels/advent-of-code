#include <iostream>
#include <fstream>
#include <vector>

int part_a()
{
    std::vector<std::string> commands;
    std::vector<int> distance;
    std::ifstream instream("input.txt");
    for(std::string line; getline(instream, line);)
    {
        commands.push_back(line.substr(0, line.find(" ")));
        distance.push_back(std::stoi(line.substr(line.find(" ") + 1, line.size()-1)));
    }

    int horizontal_position = 0;
    int depth_position = 0;

    for(int i=0; i<commands.size(); i++)
    {
        if(commands[i] == "forward")
        {
            horizontal_position += distance[i];
        }
        else if(commands[i] == "down")
        {
            depth_position += distance[i];
        }
        else if(commands[i] == "up")
        {
            depth_position -= distance[i];
        }
    }

    return horizontal_position * depth_position;
}

int part_b()
{
    std::vector<std::string> commands;
    std::vector<int> distance;
    std::ifstream instream("input.txt");
    for(std::string line; getline(instream, line);)
    {
        commands.push_back(line.substr(0, line.find(" ")));
        distance.push_back(std::stoi(line.substr(line.find(" ") + 1, line.size()-1)));
    }

    int horizontal = 0;
    int aim = 0;
    int depth = 0;

    for(int i=0; i<commands.size(); i++)
    {
        if(commands[i] == "forward")
        {
            horizontal += distance[i];
            depth += (aim * distance[i]);
        }
        else if(commands[i] == "down")
        {
            aim += distance[i];
        }
        else if(commands[i] == "up")
        {
            aim -= distance[i];
        }
    }

    return horizontal * depth;
}

int main()
{
    std::cout << part_a() << std::endl;
    std::cout << part_b() << std::endl;
}
