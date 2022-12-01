#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int getSeatFromDirections(string directions) {
    int maxRow = 127;
    int minRow = 0;
    int maxCol = 7;
    int minCol = 0;
    int res;

    for(int i=0; i<7; i++) {
        if(directions[i] == 'F') {
            maxRow = minRow + ((maxRow-minRow) / 2);
        }
        else if(directions[i] == 'B') {
            minRow = maxRow - ((maxRow-minRow)/2);
        }
    }

    for(int i=7; i<10; i++) {
        if(directions[i] == 'L') {
            maxCol = minCol + ((maxCol-minCol) / 2);
        }
        else if(directions[i] == 'R') {
            minCol = maxCol - ((maxCol-minCol)/2);
        }
    }
    res = maxRow*8 + maxCol;
    return res;
}

int main() {
	int maxSeat = 0;
	ifstream input("input_data.txt");
	for(string line; getline(input, line);) {
		int seat = getSeatFromDirections(line);
		if(seat > maxSeat) {
			maxSeat = seat;
		}
	}
	cout << "Max seat: " << maxSeat << endl;
}
