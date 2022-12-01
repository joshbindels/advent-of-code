#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef enum {
    EMPTY,
    TAKEN,
    FLOOR
} POS_STATUS;


void loadData(vector<vector<POS_STATUS>>& out) {
#ifdef TEST
    ifstream input("test_data.txt");
#else
    ifstream input("input_data.txt");
#endif
    for(string line; getline(input, line);) {
        vector<POS_STATUS> o;
        for(const char& c: line) {
            switch(c) {
                case 'L':
                    o.push_back(POS_STATUS::EMPTY);
                    break;
                case '.':
                    o.push_back(POS_STATUS::FLOOR);
                    break;
                case '#':
                    o.push_back(POS_STATUS::TAKEN);
                    break;
                default: break;
            }
        }
        out.push_back(o);
    }
}

int get_empty_seats_in_direction(const vector<vector<POS_STATUS>>& inp, int pos_y, int pos_x, int mov_y, int mov_x) {
    if(pos_x < 0 || pos_x > inp[0].size()-1 || pos_y < 0 || pos_y > inp.size()-1) {
        return 1;
    }
    else if(inp[pos_y][pos_x] == FLOOR) {
        return get_empty_seats_in_direction(inp, pos_y + mov_y, pos_x + mov_x, mov_y, mov_x);
    }
    else if(inp[pos_y][pos_x] == EMPTY) {
        return 1;
    }
    return 0;
}

bool iterate(vector<vector<POS_STATUS>>& inp, vector<vector<POS_STATUS>>& out) {
#define UP      -1
#define DOWN    1
#define LEFT    -1
#define RIGHT   1
#define STAY    0
    bool has_changed = false;
    for(int y=0; y<inp.size(); y++) {
        vector<POS_STATUS> line_out;
        for(int x=0; x<inp[0].size(); x++) {

            if(inp[y][x] == FLOOR) {
                line_out.push_back(FLOOR);
                continue;
            }
            int emptyseats = 0;
            emptyseats += get_empty_seats_in_direction(inp, y+UP,   x+LEFT,   UP,   LEFT);
            emptyseats += get_empty_seats_in_direction(inp, y+UP,   x,        UP,   STAY);
            emptyseats += get_empty_seats_in_direction(inp, y+UP,   x+RIGHT,  UP,   RIGHT);
            emptyseats += get_empty_seats_in_direction(inp, y,      x+LEFT,   STAY, LEFT);
            emptyseats += get_empty_seats_in_direction(inp, y,      x+RIGHT,  STAY, RIGHT);
            emptyseats += get_empty_seats_in_direction(inp, y+DOWN, x+LEFT,   DOWN, LEFT);
            emptyseats += get_empty_seats_in_direction(inp, y+DOWN, x,        DOWN, STAY);
            emptyseats += get_empty_seats_in_direction(inp, y+DOWN, x+RIGHT,  DOWN, RIGHT);


            if(inp[y][x] == EMPTY && emptyseats == 8) {
                line_out.push_back(TAKEN);
                has_changed = true;
            }
            else if(inp[y][x] == TAKEN && emptyseats < 4) {
                 line_out.push_back(EMPTY);
                 has_changed = true;
            }
            else {
                line_out.push_back(inp[y][x]);
            }
        }
        out.push_back(line_out);
    }
    return has_changed;
}

int get_num_of_taken_seats(const vector<vector<POS_STATUS>>& inp) {
    int res = 0;
    for(const vector<POS_STATUS>& line: inp) {
        for(const POS_STATUS& p: line) {
            if(p == TAKEN) res++;
        }
    }
    return res;
}

int main() {
    vector<vector<POS_STATUS>> seating;
    loadData(seating);

    //printSeating(seating);
    vector<vector<POS_STATUS>> after;

    int i=0;
    while(iterate(seating, after)) {
        cout << "Iteration " << i++ << endl;
        seating = after;
        after.erase(after.begin(), after.end());
    }

    cout << "Number of occupied seats: " << get_num_of_taken_seats(after) << endl;

    return 0;
}
