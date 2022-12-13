#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


class file //everything is a file like linux
{
public:
    file(std::string name, int size=0) :name(name), size(size) {}
    void add_file(file& f) { this->files.push_back(f); }

    int get_size_on_disk() const
    {
        int total_size = 0;
        for(const file& f: this->files)
        {
            total_size += f.size == 0 ? f.get_size_on_disk() : f.size;
        }
        return total_size;
    }

    file& get_file_with_name(std::string name)
    {
        for(file& f: files)
        {
            if(f.name == name)
            {
                return f;
            }
        }
        return *this;
    }

    std::string name;
    int size;
    std::vector<file> files;
};

void part_a()
{
    std::stack<file> st;
    file root("/");
    st.push(root);
    std::ifstream instream("input.txt");

    for(std::string line; getline(instream, line);)
    {
        if(line[0] == '$') // command
        {
        }
        else // file name
        {
            if(line.substr(0,3) == "dir") // directory
            {
                file d(line.substr(5, line.length()));
                st.top().add_file(d);
            }
            else
            {
                int div_index = line.find(" ");
                file f(line.substr(div_index+1, line.length()), std::stoi(line.substr(0,div_index-1)));
                st.top().add_file(f);
            }
        }
    }
}

void part_b()
{
}

int main()
{
    part_a();
    part_b();
    return 0;
}
