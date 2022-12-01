#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

typedef struct {
    int il;
    int ih;
    char token;
    string password;
} password_entry;

password_entry* getEntryFromFileLine(const string& line)
{
        password_entry* res = (password_entry*)malloc(sizeof(password_entry));
        char password[50];
        char l[50];
        strcpy(l,  line.c_str());
        sscanf(l, "%d-%d %c: %50s", &res->il, &res->ih, &res->token, password);
        string pwd(password);
        res->password = pwd;
        return res;
}

bool XOR(bool a, bool b)
{
    return (a + b) % 2;
}

int main() {
    int valid_count = 0;
    ifstream input("input_data.txt");
    for(string line; getline(input, line);)
    {
            password_entry* entry = getEntryFromFileLine(line);

            if(XOR(entry->password[entry->il-1]==entry->token, entry->password[entry->ih-1]==entry->token))
            {
                    valid_count++;
            }
            free(entry);
    }

    cout << "Number of correct passwords: " << valid_count << endl;
    return 0;
}
