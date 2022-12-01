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
    vector<string> validEcl{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    int numOfValidPassports = 0;
    int validFields = 0;
    int tmpnum = 0;
    ifstream input("input_data.txtraz");
    for(string line; getline(input, line);)
    {
        if(line.length() == 0) {
            if(validFields == 7) {
                numOfValidPassports++;
            }
            validFields = 0;
            continue;
        }
        vector<string> key_value_pairs;
        tokenize(line, ' ', key_value_pairs);
        for(const string& word: key_value_pairs) {
            vector<string> values;
            tokenize(word, ':', values);

            if(values.at(0) == "byr") {
                tmpnum = stoi(values.at(1));
                if(tmpnum > 1919 && tmpnum < 2003) {
                    validFields++;
                }
            }
            else if(values.at(0) == "iyr") {
                tmpnum = stoi(values.at(1));
                if(tmpnum > 2009 && tmpnum < 2021) {
                    validFields++;
                }
            }
            else if(values.at(0) == "eyr") {
                tmpnum = stoi(values.at(1));
                if(tmpnum > 2019 && tmpnum < 2031) {
                    validFields++;
                }
            }
            else if(values.at(0) == "hgt") {
                if(values.at(1).find("cm") != string::npos) {
                    tmpnum = stoi(values.at(1).substr(0, values.at(1).length() - 2));
                    if(tmpnum > 149 && tmpnum < 194) {
                        validFields++;
                    }
                }
                else if(values.at(1).find("in") != string::npos) {
                    tmpnum = stoi(values.at(1).substr(0, values.at(1).length() - 2));
                    if(tmpnum > 58 && tmpnum < 77) {
                        validFields++;
                    }
                }
            }
            else if(values.at(0) == "hcl") {
                if(values.at(1)[0] == '#' && values.at(1).length() == 7) {
                    validFields++;
                }
            }
            else if(values.at(0) == "ecl") {
                if(find(validEcl.begin(), validEcl.end(), values.at(1)) != validEcl.end()) {
                    validFields++;
                }
            }
            else if(values.at(0) == "pid") {
                if(values.at(1).length() == 9 && values.at(1).find_first_not_of("0123456789") == string::npos) {
                    validFields++;
                }
            }
        }
    }
    if(validFields == 7) numOfValidPassports++;
    cout << numOfValidPassports << " valid passports." << endl;

}
