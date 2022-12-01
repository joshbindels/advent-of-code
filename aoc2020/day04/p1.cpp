#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void printVector(const vector<string>& v)
{
    for(const string& s: v) {
        cout << s;
    }
    cout << endl;
}

void tokenize(const string& s, const char& delim, vector<string>& out) {
    stringstream ss(s);
    string line;
    while(getline(ss, line, delim)) {
        out.push_back(line);
    }
}

int main() {
    vector<string> reqFields{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    int numOfValidPassports = 0;
    int fieldCount = 0;
    ifstream input("input_data.txt");
    for(string line; getline(input, line);)
    {
        if(line.length() == 0) {
            if(fieldCount == 7) {
                numOfValidPassports++;
            }
            fieldCount = 0;
            continue;
        }
        vector<string> key_value_pairs;
        tokenize(line, ' ', key_value_pairs);
        for(const string& word: key_value_pairs) {
            vector<string> values;
            tokenize(word, ':', values);
            if(find(reqFields.begin(), reqFields.end(), values.at(0)) != reqFields.end()) {
                fieldCount++;
            }
            //printVector(values);
        }
    }
    cout << numOfValidPassports << " valid passports." << endl;

}
