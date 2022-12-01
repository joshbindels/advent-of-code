#include <iostream>
#include <fstream>
#include <algorithm>

#define LOG1(x)    cout << x << endl;
#define LOG2(x, y) cout << x << ": " << y << endl;

using namespace std;

int main() {
    ifstream input("input_data.txt");
    string answers = "";
    int correctAnswers = 0;
    bool firstline = true;
    for(string line; getline(input, line);)
    {
        if(line.length() == 0) {
            correctAnswers += answers.length();
            answers = "";
            firstline = true;
            continue;
        }
        if(firstline) {
            answers = line;
            firstline = false;
        }
        else {
            string charsToDelete = "";
            for(const char& c: answers) {
                if(line.find(c) == string::npos) {
                    charsToDelete += c;
                }
            }
            for(const char& c: charsToDelete) {
                answers.erase(remove(answers.begin(), answers.end(), c), answers.end());
            }
        }
    }
    correctAnswers += answers.length();
    cout << "Output: " << correctAnswers << endl;

}
