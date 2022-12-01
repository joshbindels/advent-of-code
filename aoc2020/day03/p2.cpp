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

int GetNumOfTrees(const vector<vector<char> >& v, int mh, int mv)
{
    const int move_horizontal = mh;
    const int move_vertical = mv;

    int cur_index_horizontal = move_horizontal;
    int level_width = v.at(0).size();
    int t = 0;

    for(int i=mv; i<v.size(); i+=move_vertical)
    {
        if(cur_index_horizontal >= level_width)
        {
            cur_index_horizontal  = cur_index_horizontal - level_width;
        }
        if(v.at(i).at(cur_index_horizontal) == '#')
        {
            t++;
        }
        cur_index_horizontal += move_horizontal;
    }
    return t;
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

    int trees1 = GetNumOfTrees(mountain, 3, 1);
    int trees2 = GetNumOfTrees(mountain, 1, 1);
    int trees3 = GetNumOfTrees(mountain, 5, 1);
    int trees4 = GetNumOfTrees(mountain, 7, 1);
    int trees5 = GetNumOfTrees(mountain, 1, 2);
    cout << "trees: " << trees1 << endl;
    cout << "trees: " << trees2 << endl;
    cout << "trees: " << trees3 << endl;
    cout << "trees: " << trees4 << endl;
    cout << "trees: " << trees5 << endl;
    cout << "total: " << (long)trees1*trees2*trees3*trees4*trees5 << endl;

}
