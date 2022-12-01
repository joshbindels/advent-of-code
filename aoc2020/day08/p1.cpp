#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

#define LOGOP(x) cout << x.first << " " << x.second << endl;

typedef enum {
    ACC,
    JMP,
    NOP
} OPS;

void parseInput(vector<pair<OPS, int>>& out);

int main() {
    vector<pair<OPS, int>> operations;
    parseInput(operations);

    int sum = 0;
    int index = 0;
    set<int> visitedIndexes;

    while(visitedIndexes.find(index) == visitedIndexes.end()) {
        visitedIndexes.insert(index);
        pair<OPS, int>& op = operations.at(index);
        switch(op.first) {
            case OPS::ACC:
                sum += op.second;
                index++;
                break;
            case OPS::JMP:
                index += op.second;
                break;
            case OPS::NOP:
                index++;
                break;
        }
    }

    cout << "Sum: " << sum << endl;

    return 0;
}


void parseInput(vector<pair<OPS, int>>& out) {
    ifstream input("input_data.txt");
    for(string line; getline(input,line);) {
        size_t pos = line.find(' ');
        string op = line.substr(0, pos);
        int val = stoi(line.substr(pos));
        OPS ops;
        if(op == "acc") {
            ops = ACC;
        }
        else if (op == "jmp") {
            ops = JMP;
        }
        else if (op == "nop") {
            ops = NOP;
        }

        out.push_back({ops, val});
    }
}
