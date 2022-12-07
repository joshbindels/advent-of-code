#include <iostream>
#include <fstream>
#include <set>

bool hasDuplicate(const std::string& s, int len)
{
    std::set<char> c;
    for(int i=0; i<len; i++)
    {
        if(!c.insert(s[i]).second)
            return true;
    }
    return false;
}

void part_a()
{
    std::ifstream instream("input.txt");
    std::string sequence;
    std::getline(instream, sequence);

    for(int i=0; i<sequence.length(); i++)
    {
        std::string cur_str = sequence.substr(i, i+4);
        if(!hasDuplicate(cur_str, 4))
        {
            std::cout << "part a: " << i + 4 << std::endl;;
            return;
        }
    }
}


void part_b()
{
    std::ifstream instream("input.txt");
    std::string sequence;
    std::getline(instream, sequence);

    for(int i=0; i<sequence.length(); i++)
    {
        std::string cur_str = sequence.substr(i, i+14);
        if(!hasDuplicate(cur_str, 14))
        {
            std::cout << "part b: " << i + 14 << std::endl;;
            return;
        }
    }
}

int main()
{
    part_a();
    part_b();
}
