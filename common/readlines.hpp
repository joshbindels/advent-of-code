#include <fstream>
#include <vector>
#include <iostream>


using namespace std;
namespace common
{


void get_lines_from_file(const string& filename, vector<string>& out)
{
    std::ifstream instream(filename);
    for(string line; getline(instream, line);)
    {
        out.push_back(line);
    }
}

void get_lines_from_file(const string& filename, vector<int>& out)
{
    std::ifstream instream(filename);
    for(string line; getline(instream, line);)
    {
        out.push_back(std::stoi(line, nullptr, 2));
    }
}


}
