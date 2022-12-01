#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define WINDOW 25



void parseInput(vector<long>& out);


int main() {
    vector<long> values;
    parseInput(values);

    for(int i=0; i<values.size()-WINDOW; i++) {
        bool found = false;
        for(int hi=i+WINDOW-1; hi>i; hi--) {
            for(int lo=i; lo<hi; lo++) {
                if((values[lo] + values[hi]) == values[i+WINDOW]) {
                    found = true;
                }
            }
        }
        if(!found) {
            cout << "val: " << values[i+WINDOW] << endl;
            return 0;
        }
    }
}

void parseInput(vector<long>& out) {
    ifstream input("input_data.txt");
    for(string line; getline(input, line);) {
        out.push_back(stol(line));
    }
}
