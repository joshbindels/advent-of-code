#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#ifndef TEST
#define WINDOW 25
#else
#define WINDOW 5
#endif



void parseInput(vector<long>& out);


int main() {
    vector<long> values;
    parseInput(values);
    cout << "values.size: " << values.size() << endl;

    int invalidVal;
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
            invalidVal = values[i+WINDOW];
            break;
        }
    }

    int hi, lo = 0;
    bool found = false;
    for(int i=0; i<values.size(); i++) {
        if(found) break;
        int curVal = values[i];
        for(int j=i+1; j<values.size(); j++) {
            if(curVal + values[j] < invalidVal) {
                curVal += values[j];
                continue;
            }
            else if(curVal + values[j] == invalidVal) {
                lo = i;
                hi = j;
                found = true;
                break;
            }
            else if(curVal + values[j] > invalidVal) {
                break;
            }
        }
    }
    long max_val = *max_element(begin(values) + lo, begin(values) + hi);
    long min_val = *min_element(begin(values) + lo, begin(values) + hi);
    cout << "Max: " << max_val << " Min: " << min_val << " min + max = " << min_val + max_val << endl;
}

void parseInput(vector<long>& out) {
#ifndef TEST
    ifstream input("input_data.txt");
#else
    ifstream input("test_data.txt");
#endif
    for(string line; getline(input, line);) {
        out.push_back(stol(line));
    }
}
