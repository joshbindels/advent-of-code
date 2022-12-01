#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printVector(const vector<vector<char> >* v)
{
    for(const vector<char>& l: *v) {
        for(const char& c: l) {
            cout << c;
        }
        cout << endl;
    }

}

int main() {
    //char mountain[][31] = {};
    vector<vector<char> > mountain;
    ifstream input("input_data.txt");
    for(string line; getline(input, line);)
    {
        vector<char> level;
        for(const char& c : line) {
            level.push_back(c);
        }
        mountain.push_back(level);
    }

    const int move_horizontal = 3;
    const int move_vertical = 1;

    int cur_index_horizontal = move_horizontal;
    int level_width = mountain.at(0).size();
    int o = 0;
    int t = 0;

    for(int i=1; i<mountain.size(); i+=move_vertical)
    {
        if(cur_index_horizontal >= level_width)
        {
            cur_index_horizontal  = cur_index_horizontal - level_width;
        }
        if(mountain.at(i).at(cur_index_horizontal) == '#')
        {
            t++;
        }
        else
        {
            o++;
        }
        cur_index_horizontal += move_horizontal;

    }

    cout << "o: " << o << endl;
    cout << "t: " << t << endl;
}
