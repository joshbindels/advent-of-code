#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <regex>

using namespace std;

vector<string> test_input = {
    "two1nine",
    "eightwothree",
    "abcone2threexyz",
    "xtwone3four",
    "4nineeightseven2",
    "zoneight234",
    "7pqrstsixteen",
};

vector<int> expected_outputs = {29, 83, 13, 24, 42, 14, 76};

int convert(const string& si, size_t index)
{
    vector<string> num_words = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };
    map<string, int> nums = {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9},
    };
    for ( string& num: num_words )
    {
        if ( si.substr(index, num.length()) == num )
        {
            return nums[num];
        }
    }
    return -1;
};

int get_val_for_string(const string& s)
{

	int res;
	// Left
	for (size_t i=0; i<s.length(); i++)
	{
		char c = s.at(i);
		if ( isdigit(c) )
		{
			res = atoi(&c);
			res *= 10;
			break;
		}
        int z = convert(s, i);
        if ( z > -1 )
        {
            res = z;
            res *= 10;
            break;
        }
	}

	// Go right
	for (size_t i=s.length() - 1; i>=0; i--)
	{
		char c = s.at(i);
		if ( isdigit(c) )
		{
			res += atoi(&c);
			break;
		}
        int z = convert(s, i);
        if ( z > -1 )
        {
            res += z;
            break;
        }
	}
	return res;
}

int main()
{
    int res = 0;
	ifstream instream("inputs/day1");
    for (string line; getline(instream, line);)
    {
        res += get_val_for_string(line);
    }
    cout << "Result: " << res << endl;
}
