#include <iostream>
#include <fstream>
#include <set>
#include <vector>

int part_a()
{
    const std::string alphabet =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::ifstream input_stream("input.txt");
    size_t total = 0;
    for(std::string line; getline(input_stream, line);)
    {
        std::string left = line.substr(0, line.length()/2);
        std::string right = line.substr(line.length()/2, line.length()-1);

        std::set<char> left_chars;

        for(char& c: left)
        {
            left_chars.insert(c);
        }

        for(char& c: right)
        {
            if(left_chars.find(c) != left_chars.end())
            {
                size_t pos = alphabet.find(c);
                total += (pos + 1);
                break;
            }
        }
    }

    return total;
}

int part_b()
{
    const std::string alphabet =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::ifstream input_stream("input.txt");
    size_t total = 0;
    std::vector<std::string> lines;
    for(std::string line; getline(input_stream, line);)
    {
        lines.push_back(line);
    }

    for(int i=0; i<lines.size(); i+=3)
    {
        std::set<char> line_one;
        for(const char& c: lines.at(i))
        {
            line_one.insert(c);
        }

        for(const char& c: lines.at(i+1))
        {
            if(line_one.find(c) != line_one.end())
            {
                if(lines.at(i+2).find(c) != std::string::npos)
                {
                    size_t pos = alphabet.find(c);
                    total += (pos + 1);
                    break;
                }
            }
        }
    }

    return total;
}


int main()
{
    std::cout << "part a: " << part_a() << std::endl;
    std::cout << "part b: " << part_b() << std::endl;
    return 0;
}
