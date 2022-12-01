#include <vector>
#include <iostream>
#include "readlines.hpp"

int part_a()
{
    int previous_number = 0;
    int number_of_increases = 0;
    std::vector<std::string> lines;
    common::get_lines_from_file("input.txt", lines);
    for(const std::string& line: lines)
    {
        int n = std::stoi(line);
        if(n > previous_number)
        {
                number_of_increases++;
        }
        previous_number = n;
    }
    return --number_of_increases;
}

int part_b()
{
    std::vector<int> numbers;
    common::get_lines_from_file("input.txt", numbers);

    int previous_number = 0;
    int num_of_increases = 0;
    for(int i=0; i<(numbers.size()-3); i++)
    {
        int num = 0;
        for(int j=0; j<3; j++)
        {
            num += numbers[i+j];
        }
        if(num > previous_number)
        {
            num_of_increases++;
        }
        previous_number = num;
    }

    return --num_of_increases;
}

int main()
{
    std::cout << "Part A: " << part_a() << std::endl;
    std::cout << "Part B: " << part_b() << std::endl;

    return 0;
}

