/*
 * Not the cleanest solution but it works!
 */
#include <iostream>
#include <fstream>
#include <vector>

//#define test

#ifdef test
#define NUM_ROWS 10
#define NUM_COLS 10
#else
#define NUM_ROWS 99
#define NUM_COLS 99
#endif

bool visibleLeft(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    for(int c=col-1; c>=0; c--)
    {
        if(v.at(row).at(c) >= tree)
        {
            return false;
        }
    }
    return true;
}

bool visibleRight(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    for(int c=col+1; c<NUM_COLS; c++)
    {
        if(v.at(row).at(c) >= tree)
        {
            return false;
        }
    }
    return true;
}

bool visibleUp(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    for(int r=row-1; r>=0; r--)
    {
        if(v.at(r).at(col) >= tree)
        {
            return false;
        }
    }
    return true;
}

bool visibleDown(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    for(int r=row+1; r<NUM_ROWS; r++)
    {
        if(v.at(r).at(col) >= tree)
        {
            return false;
        }
    }
    return true;
}

void part_a()
{
#ifdef test
    /* answer:
       outside 36
       --> <-- vv ^^
       1   0   1   0
       0   1   1   1
       0   0   0   0
       0   1   0   1
       1   1   0   0
       0   0   1   0
       1   1   1   1
       0   0   0   0
total : 14 + 36 = 50
*/
    std::vector<std::vector<int>> grid{
        {3,0,3,7,3,3,0,3,7,3},
        {2,5,5,1,2,2,5,5,1,2},
        {6,5,3,3,2,6,5,3,3,2},
        {3,3,5,4,9,3,3,5,4,9},
        {3,5,3,9,0,3,5,3,9,0},
        {3,0,3,7,3,3,0,3,7,3},
        {2,5,5,1,2,2,5,5,1,2},
        {6,5,3,3,2,6,5,3,3,2},
        {3,3,5,4,9,3,3,5,4,9},
        {3,5,3,9,0,3,5,3,9,0}
    };

/*
--> 2 2 1 3 1 1 3 2
vvv 1 1 2 1 1 2 1 1
<-- 3 1 1
std::vector<std::vector<int>> grid{
{0,4,4,2,3,4,0,4,3,1},
{2,4,4,4,0,1,3,4,3,0},
{1,2,2,0,3,0,3,1,0,4},
{2,2,0,3,3,2,4,2,0,0},
{0,2,4,3,2,0,3,1,4,5},
{4,2,2,3,1,4,3,3,3,3},
{4,0,2,4,2,2,3,4,4,2},
{2,3,4,3,1,2,2,3,4,3},
{0,4,4,4,4,1,1,3,2,5},
{5,4,5,5,4,4,3,4,1,3}};
*/

#else
    std::ifstream instream("input.txt");
    std::vector<std::vector<int>> grid(NUM_ROWS);
    int row = 0;
    for(std::string line; getline(instream, line);)
    {
        for(int col=0; col<NUM_COLS; col++)
        {
            std::string c(1, line[col]);
            grid.at(row).push_back(std::stoi(c));
        }
        row++;
    }

#endif


    int total_visible = NUM_ROWS * 2 + NUM_COLS * 2;
    total_visible -= 4;
    std::cout << "outer: " << total_visible << std::endl;;


	for(int col=1; col<NUM_COLS-1; col++)
    {
        for(int row=1; row<NUM_ROWS-1; row++)
        {
            int tree = grid.at(row).at(col);
            // Check left
            bool l = visibleLeft(col, row, tree, grid);
            bool r = visibleRight(col, row, tree, grid);
            bool u = visibleUp(col, row, tree, grid);
            bool d = visibleDown(col, row, tree, grid);
            if(l || r || u || d){ total_visible++;
            std::cout << "(" << col << "," << row << ") " <<
                (l ? "t" : "f") << " - " <<
                (r ? "t" : "f") << " - " <<
                (u ? "t" : "f") << " - " <<
                (d ? "t" : "f") << " - " << std::endl;
            }
        }
    }

    std::cout << "total: " << total_visible << std::endl;
}


int getNumLeft(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    int res = 0;
    for(int c=col-1; c>=0; c--)
    {
        if(v.at(row).at(c) < tree){ res++; }
        else if(v.at(row).at(c) >= tree) { return ++res; }
    }
    return res;
}
int getNumRight(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    int res = 0;
    for(int c=col+1; c<NUM_COLS; c++)
    {
        if(v.at(row).at(c) < tree){ res++; }
        else if(v.at(row).at(c) >= tree) { return ++res; }
    }
    return res;
}
int getNumUp(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    int res = 0;
    for(int r=row-1; r>=0; r-- )
    {
        if(v.at(r).at(col) < tree){ res++; }
        else if(v.at(r).at(col) >= tree) { return ++res; }
    }
    return res;
}
int getNumDown(int col, int row, int tree, std::vector<std::vector<int>>& v)
{
    int res = 0;
    for(int r=row+1; r<NUM_ROWS; r++)
    {
        if(v.at(r).at(col) < tree){ res++; }
        else if(v.at(r).at(col) >= tree) { return ++res; }
    }
    return res;
}
void part_b()
{
    std::ifstream instream("input.txt");
    std::vector<std::vector<int>> grid(NUM_ROWS);
    int row = 0;
    for(std::string line; getline(instream, line);)
    {
        for(int col=0; col<NUM_COLS; col++)
        {
            std::string c(1, line[col]);
            grid.at(row).push_back(std::stoi(c));
        }
        row++;
    }

    int cur_max = 0;
	for(int col=0; col<NUM_COLS; col++)
    {
        for(int row=0; row<NUM_ROWS; row++)
        {
            int tree = grid.at(row).at(col);
            int m = getNumUp(col, row, tree, grid)
                * getNumDown(col, row, tree, grid)
                * getNumLeft(col, row, tree, grid)
                * getNumRight(col, row, tree, grid);
            cur_max = (m > cur_max) ? m : cur_max;
        }
    }
    std::cout << "max: " << cur_max << std::endl;


}

int main()
{
    part_a();
    part_b();
    return 0;
}

