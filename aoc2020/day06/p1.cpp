#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ifstream input("input_data.txt");
    string answers = "";
    int correctAnswers = 0;
    for(string line; getline(input, line);)
    {
        if(line.length() == 0) {
            correctAnswers += answers.length();
            answers = "";
            continue;
        }
        for(const char& c: line) {
            if(answers.length() == 0) {
                answers += c;
            }
            else if(answers.find(c) == string::npos) {
                answers += c;
            }
        }
    }
    correctAnswers += answers.length();
    cout << "Output: " << correctAnswers << endl;

}
