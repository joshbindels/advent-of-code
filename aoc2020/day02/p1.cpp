#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main() {
    int valid_count = 0;
    ifstream input("input_data.txt");
    for(string line; getline(input, line);)
    {
            int cl, ch;
            char token;
            char password[50];

            char l[50];
            strcpy(l,  line.c_str());

            sscanf(l, "%d-%d %c: %50s", &cl, &ch, &token, password);

            string pwd(password);
            int cnt = count(pwd.begin(), pwd.end(), token);
            if(cnt >= cl && cnt <= ch) {
                    valid_count++;
            }

    }

    cout << "Number of correct passwords: " << valid_count << endl;
    return 0;
}
