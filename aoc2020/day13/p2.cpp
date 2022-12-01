#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

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
            buses.push_back(-1);
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


    long long start_t = (long)*max_element(begin(buses), end(buses));
    int increment = start_t;
    //long long start_t = 10000000;
    bool found = true;

    while(1) {
        cout << "t:" << start_t << endl;
        long long  cur_t = start_t;
        for(const int& bus: buses) {
            if(bus == -1) {
                cur_t++;
                continue;
            }
            if(cur_t % bus != 0) {
                found = false;
                break;
            }
            cur_t++;
        }
        if(found) {
            break;
        }
        start_t += increment;
    }

    cout << "Solution time: " << start_t << endl;



    return 0;
}

