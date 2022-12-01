#include <iostream>
#include <fstream>
#include <vector>

int part_a()
{
    std::ifstream instream("input.txt");
    int cur_max = 0;
    int cur_count = 0;
    for(std::string line; getline(instream, line);)
    {
		if(line == "")
        {
            cur_max = (cur_count > cur_max) ? cur_count : cur_max;
            cur_count = 0;
        }
		else
		{
			cur_count += std::stoi(line);
		}
    }
    return cur_max;
}

int part_b()
{
    std::ifstream instream("input.txt");
	std::vector<int> counts;
    int cur_count = 0;
    for(std::string line; getline(instream, line);)
    {
		if(line == "")
        {
			counts.push_back(cur_count);
            cur_count = 0;
        }
		else
		{
			cur_count += std::stoi(line);
		}
    }
	std::sort(counts.begin(), counts.end());
	std::reverse(counts.begin(), counts.end());
    return counts.at(0) + counts.at(1) + counts.at(2);
}

int main()
{
    std::cout << "Part a: " << part_a() << std::endl;
    std::cout << "Part b: " << part_b() << std::endl;
	return 0;
}
