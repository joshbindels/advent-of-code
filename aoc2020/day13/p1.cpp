#include <iostream>
#include <fstream>
#include <vector>

#define LOG(X, Y) std::cout << X << " " << Y << std::endl;
#ifdef TEST
#define DLOG(X, Y) LOG(X, Y)
#else
#define DLOG(X,Y)
#endif

using namespace std;

void loadData(int& timestamp, vector<int>& buses) {
#ifdef TEST
    ifstream input("test_data.txt");
#else
    ifstream input("input_data.txt");
#endif
    string line;
    // Get timestamp
    getline(input, line);
    DLOG("line", line);
    timestamp = stoi(line);
    for(string c; getline(input, c, ',');) {
        DLOG("c", c);
        if(c == "x") {
            continue;
        }
        buses.push_back(stoi(c));
    }
}

void printVector(vector<int>& inp) {
    cout << "<";
    for(const int& i: inp) {
        cout << i;
        cout << ",";
    }
    cout << ">" << endl;
}



int main() {
    int target_time;
    vector<int> buses;
    loadData(target_time, buses);
    DLOG("Target_time", target_time);
    printVector(buses);
    int depart_bus;
    int depart_time = target_time*2;
    for(const int& bus: buses) {
        int earliest_time = ((target_time / bus) * bus) + bus;
        if(earliest_time < depart_time) {
            depart_time = earliest_time;
            depart_bus = bus;
        }
    }
    LOG("Bus", depart_bus);
    LOG("depart_time", depart_time);
    LOG("Answer: id x waittime = ", depart_bus * (depart_time - target_time))
    return 0;
}

