#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//vector<string> test_input = {
//".479........155..............944.....622..............31.........264.......................532..........................254.........528.....",
//"..............-...............%.....+...................=....111*.................495.......+.......558..................../..........*.....",
//"....................791*..62.....$.............847........&........-..........618.*...........818....&..642.........................789.....",
//};

vector<string> test_input = {
    "467..114..",
    "...*......",
    "..35..633.",
    "...3..#...",
    "617*5.....",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.."
};

int get_left(vector<string>& t, int row, int col, int& matched)
{
    int res = 0;
    if ( col == 0 )
    {
        return res;
    }

    int start = col - 1;
    int end = -1;

    for ( int i=start; i>=0; i--)
    {
        if ( !isdigit(t.at(row).at(i)) )
        {
            break;
        }
        end = i;
    }

    if (end == -1)
    {
        return res;
    }
    string val = t.at(row).substr(end, (start - end) + 1);

    res = stoi(val);
    matched++;
    return res;
}

int get_right(vector<string>& t, int row, int col, int& matched)
{
    int width = t.at(row).size();
    int res = 0;
    if ( col == width - 1 )
    {
        return res;
    }

    int start = col + 1;
    int end = -1;
    for ( int i=start; i<width; i++)
    {
        if ( !isdigit(t.at(row).at(i)) )
        {
            break;
        }
        end = i;
    }

    if (end == -1)
    {
        return res;
    }
    string val = t.at(row).substr(start, (end - start) + 1);

    res = stoi(val);
    matched++;
    return res;
}

int get_row(vector<string>& t, int row, int col, int& matched)
{
    int res = 0;
    if ( row < 0 )
    {
        return 0;
    }
    if ( row > t.size() - 1 )
    {
        return 0;
    }

    if ( isdigit(t.at(row).at(col)) )
    {
        // go left and right
        int start = col;
        int end = -1;

        for ( int i=start; i>=0; i-- )
        {
            if ( !isdigit(t.at(row).at(i)) )
            {
                break;
            }
            start = i;
        }

        for ( int i=col; i<t.at(row).size() - 1; i++ )
        {
            if ( !isdigit(t.at(row).at(i)) )
            {
                break;
            }
            end = i;
        }

        if ( end == -1)
        {
            return 0;
        }
        string val = t.at(row).substr(start, (end - start) + 1);
        res = stoi(val);
        matched++;
        return res;
    }
    else
    {
        int top_left = get_left(t, row, col, matched);
        int top_right = get_right(t, row, col, matched);
        return std::max(top_left, 1) * std::max(top_right, 1);
    }
    return 0;
}

int main()
{
    #define TEST 0
    #if TEST
    vector<string>& target = test_input;
    #else
    vector<string> target;
    ifstream instream("inputs/day3");
    for (string line; getline(instream, line);)
    {
        target.push_back(line);
    }
    #endif

    //string symbols = "!@#*+&=+$/%-";
    string symbols = "*";
    int res = 0;
    for( size_t row=0; row<target.size(); row++ )
    {
        for( size_t col=0; col<target.at(row).size(); col++ )
        {
            if ( symbols.find(target.at(row).at(col)) != string::npos )
            {
                int matched = 0;
                int left = get_left(target, row, col, matched);
                int right = get_right(target, row, col, matched);
                int top = get_row(target, row-1, col, matched);
                int bottom = get_row(target, row+1, col, matched);

                if(matched == 2)
                {
                    int tmp = 1;
                    if (left > 0) tmp *= left;
                    if(right > 0)tmp *= right;
                    if(top > 0) tmp *= top;
                    if(bottom > 0)tmp *= bottom;
                    res += tmp;
                }

            }
        }
    }
    cout << res << endl;
    return 0;
}
