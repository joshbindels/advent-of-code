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

class Waypoint {
public:
    Waypoint() {}
    ~Waypoint() {}
    void HandleCommand(pair<OPS::OPS, int>& command);
    int GetX() { return m_PosX; }
    int GetY() { return m_PosY; }
private:
    int m_PosX = 10;
    int m_PosY = 1;
    FACE_DIR::FACE_DIR m_CurDir = FACE_DIR::N;
    void Rotate(TURN_DIR::TURN_DIR dir, int value);
    void TurnLeft();
    void TurnRight();
    void SwapXYPos();
};

void Waypoint::HandleCommand(pair<OPS::OPS, int>& command) {
    switch(command.first) {
        case OPS::N:
            m_PosY += command.second;
            break;
        case OPS::E:
            m_PosX += command.second;
            break;
        case OPS::S:
            m_PosY -= command.second;
            break;
        case OPS::W:
            m_PosX -= command.second;
            break;
        case OPS::L:
            Rotate(TURN_DIR::L, command.second);
            break;
        case OPS::R:
            Rotate(TURN_DIR::R, command.second);
            break;
        default:
            break;
    }
}

void Waypoint::Rotate(TURN_DIR::TURN_DIR dir, int value) {
    int turns = (value / 90) % 4;
    for(int i=0; i<turns; i++) {
        if(dir == TURN_DIR::R) {
            TurnRight();
        }
        else if(dir == TURN_DIR::L) {
            TurnLeft();
        }
    }
}

void Waypoint::SwapXYPos() {
    m_PosY += m_PosX;
    m_PosX = m_PosY - m_PosX;
    m_PosY -= m_PosX;
}

void Waypoint::TurnRight() {
    SwapXYPos();
    switch(m_CurDir) {
        case FACE_DIR::N:
        case FACE_DIR::S:
            m_PosY *= -1;
            break;
        case FACE_DIR::E:
        case FACE_DIR::W:
            m_PosX *= -1;
            break;
    }
}

void Waypoint::TurnLeft() {
    SwapXYPos();
    switch(m_CurDir) {
        case FACE_DIR::N:
        case FACE_DIR::S:
            m_PosX *= -1;
            break;
        case FACE_DIR::E:
        case FACE_DIR::W:
            m_PosY *= -1;
            break;
    }
}


class Ferry {
public:
    Ferry() {}
    ~Ferry() {}
    int GetPosY() { return m_PosVertical; }
    int GetPosX() { return m_PosHorizontal; }
    void HandleCommand(pair<OPS::OPS, int>& command);
    Waypoint m_Waypoint;
private:
    int m_PosHorizontal = 0;
    int m_PosVertical = 0;
private:
    void Forward(int value);
};

void Ferry::HandleCommand(pair<OPS::OPS, int>& command) {
    if(command.first == OPS::F) {
        Forward(command.second);
    }
    else {
        m_Waypoint.HandleCommand(command);
    }
}

void Ferry::Forward(int value) {
    m_PosHorizontal += (m_Waypoint.GetX() * value);
    m_PosVertical += (m_Waypoint.GetY() * value);
}




int main() {
    deque<pair<OPS::OPS, int>> data;
    loadData(data);

    Ferry ferry;

    while(!data.empty()) {
        ferry.HandleCommand(data.front());
        data.pop_front();
    }

    int x = ferry.GetPosX();
    int y = ferry.GetPosY();
    cout << "y: " << x << endl;
    cout << "x: " << y << endl;
    cout << abs(x) << " + " << abs(y) << " = " << abs(x) + abs(y) << endl;
    return 0;
}

