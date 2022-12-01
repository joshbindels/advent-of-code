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

void RunOperations(vector<pair<OPS, int>>& ops, bool& reachedEnd, int& val) {
    int index = 0;
    set<int> visitedIndexes;
    reachedEnd = false;

    while(visitedIndexes.find(index) == visitedIndexes.end()) {
        visitedIndexes.insert(index);
        pair<OPS, int>& op = ops.at(index);
        switch(op.first) {
            case OPS::ACC:
                val += op.second;
                index++;
                break;
            case OPS::JMP:
                index += op.second;
                break;
            case OPS::NOP:
                index++;
                break;
        }
        if(index == ops.size() - 1) {
            reachedEnd = true;;
            break;
        }
    }
}

int main() {
    vector<pair<OPS, int>> operations;
    parseInput(operations);


    for(int i=0; i<operations.size(); i++) {
        OPS ogOp;
        if(operations[i].first == OPS::NOP) {
            operations[i].first = OPS::JMP;
            ogOp = OPS::NOP;
        }
        else if(operations[i].first == OPS::JMP) {
            operations[i].first = OPS::NOP;
            ogOp = OPS::JMP;
        }
        else {
            continue;
        }
        bool reachedEnd = false;
        int sum = 0;
        RunOperations(operations, reachedEnd, sum);
        if(reachedEnd) {
            cout << "Sum: " << sum << endl;
            break;
        }
        operations[i].first = ogOp;
    }

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
