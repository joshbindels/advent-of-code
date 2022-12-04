#include <iostream>
#include <fstream>

#define print(x, y) std::cout << x << ": " << y << std::endl;
#define print(x,y)

int part_a()
{
    int counter = 0;
    std::ifstream instream("input.txt");
    for(std::string line; getline(instream, line);)
    {
        std::string left = line.substr(0, line.find(","));
        std::string right = line.substr(line.find(",")+1, line.length()-1);

        int low_left = std::stoi(left.substr(0, left.find("-")));
        int high_left = std::stoi(left.substr(left.find("-")+1, left.length()-1));
        int low_right = std::stoi(right.substr(0, right.find("-")));
        int high_right = std::stoi(right.substr(right.find("-")+1, right.length()-1));

        if (low_left <= low_right && high_left >= high_right)
        {
            counter++;
        }
        else if(low_right <= low_left && high_right >= high_left)
        {
            counter++;
        }
    }

    return counter;
}

int part_b()
{
    int counter = 0;
    std::ifstream instream("input.txt");
    for(std::string line; getline(instream, line);)
    {
        std::string left = line.substr(0, line.find(","));
        std::string right = line.substr(line.find(",")+1, line.length()-1);

        int low_left = std::stoi(left.substr(0, left.find("-")));
        int high_left = std::stoi(left.substr(left.find("-")+1, left.length()-1));
        int low_right = std::stoi(right.substr(0, right.find("-")));
        int high_right = std::stoi(right.substr(right.find("-")+1, right.length()-1));

        if(low_left <= high_right && low_left >= high_right)
        {
            counter++;
        }
        else if(high_left >= low_right && high_left <= high_right)
        {
            counter++;
        }
        else if(low_right <= high_left && low_right >= high_left)
        {
            counter++;
        }
        else if(high_right >= low_left && high_right <= high_left)
        {
            counter++;
        }
    }

    return counter;
}
int main()
{
    std::cout << "Part a: " << part_a() << std::endl;
    std::cout << "Part b: " << part_b() << std::endl;
    return 0;
}
