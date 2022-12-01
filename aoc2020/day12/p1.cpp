#include <iostream>
#include <fstream>
#include <deque>
#include <utility>

using namespace std;

namespace TURN_DIR {
    typedef enum {
        L,
        R
    } TURN_DIR;
}
namespace FACE_DIR {
    typedef enum {
        N,
        E,
        S,
        W
    } FACE_DIR;
}

namespace OPS {
    typedef enum {
        N,
        E,
        S,
        W,
        F,
        L,
        R
    } OPS;
}

OPS::OPS char_to_op(const char& c) {
    switch(c) {
        case 'N':
            return OPS::N;
        case 'E':
            return OPS::E;
        case 'S':
            return OPS::S;
        case 'W':
            return OPS::W;
        case 'F':
            return OPS::F;
        case 'L':
            return OPS::L;
        case 'R':
            return OPS::R;
    }
    return OPS::N;
}

void loadData(deque<pair<OPS::OPS, int>>& out) {
#ifdef TEST
    ifstream input("test_data.txt");
#else
    ifstream input("input_data.txt");
#endif
    for(string line; getline(input, line);) {
        char op = line[0];
        int val = stoi(line.substr(1));
        out.push_back({char_to_op(op), val});
    }
}

class Ferry {
public:
    Ferry() {}
    ~Ferry() {}
    FACE_DIR::FACE_DIR GetCurDir() { return m_CurDir; }
    int GetPosY() { return m_PosHorizontal; }
    int GetPosX() { return m_PosVertical; }
    void HandleCommand(pair<OPS::OPS, int>& command);
private:
    FACE_DIR::FACE_DIR m_CurDir = FACE_DIR::E;
    int m_PosHorizontal = 0;
    int m_PosVertical = 0;
private:
    void Rotate(TURN_DIR::TURN_DIR dir, int value);
    void Forward(int value);
};

void Ferry::HandleCommand(pair<OPS::OPS, int>& command) {
    switch(command.first) {
        case OPS::N:
            m_PosVertical += command.second;
            break;
        case OPS::S:
            m_PosVertical -= command.second;
            break;
        case OPS::E:
            m_PosHorizontal += command.second;
            break;
        case OPS::W:
            m_PosHorizontal -= command.second;
            break;
        case OPS::L:
            Rotate(TURN_DIR::L, command.second);
            break;
        case OPS::R:
            Rotate(TURN_DIR::R, command.second);
            break;
        case OPS::F:
            Forward(command.second);
            break;
    }
}

void Ferry::Rotate(TURN_DIR::TURN_DIR dir, int value) {
    int turns = (value / 90) % 4;
    for(int i=0; i<turns; i++) {
        switch(m_CurDir) {
            case FACE_DIR::N:
                m_CurDir = (dir == TURN_DIR::R) ? FACE_DIR::E : FACE_DIR::W;
                break;
            case FACE_DIR::E:
                m_CurDir = (dir == TURN_DIR::R) ? FACE_DIR::S : FACE_DIR::N;
                break;
            case FACE_DIR::S:
                m_CurDir = (dir == TURN_DIR::R) ? FACE_DIR::W : FACE_DIR::E;
                break;
            case FACE_DIR::W:
                m_CurDir = (dir == TURN_DIR::R) ? FACE_DIR::N : FACE_DIR::S;
                break;
        }
    }
}

void Ferry::Forward(int value) {
    switch(m_CurDir) {
        case FACE_DIR::N:
            m_PosVertical += value;
            break;
        case FACE_DIR::E:
            m_PosHorizontal += value;
            break;
        case FACE_DIR::S:
            m_PosVertical -= value;
            break;
        case FACE_DIR::W:
            m_PosHorizontal -= value;
            break;
    }
}


int main() {
    deque<pair<OPS::OPS, int>> data;
    loadData(data);

    Ferry ferry;

    for(pair<OPS::OPS,int> c: data) {
        //cout << "C: " << c.first << "," << c.second << endl;
        ferry.HandleCommand(c);
    }

    int x = ferry.GetPosX();
    int y = ferry.GetPosY();
    cout << "y: " << x << endl;
    cout << "x: " << y << endl;
    cout << abs(x) << "+" << abs(y) << " = " << abs(x) + abs(y) << endl;
    return 0;
}

