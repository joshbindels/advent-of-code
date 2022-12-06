#include <iostream>
#include <fstream>
#include <vector>


template <class T>
void printV(std::vector<std::vector<T>>& v)
{
    for(int line=0; line<v.size(); line++)
    {
        std::cout << line << " { ";
        for(const T& c: v.at(line))
        {
            std::cout << c << " , ";
        }
        std::cout << std::endl;
    }
}

template <class T>
std::stack<T> construct_stack_from_vector(std::vector<T>& v)
{
    std::stack<T> res;

    for(auto it=rbegin(v); it!=rend(v); it++)
    {
        res.push(*it);
    }
    return res;
}

int part_a()
{
    std::ifstream instream("input.txt");
    std::vector<std::vector<char>> containers_v(9);
    std::vector<std::vector<int>> actions;
    std::vector<std::stack<char>> containers;

    int line_count = 1;

    for(std::string line; getline(instream, line);)
    {
        if (line_count < 9)
        {
            size_t last_pos = 0;
            size_t pos = line.find("[", last_pos);
            while(pos != std::string::npos)
            {
                containers_v.at(pos/4).push_back(line[pos+1]);
                last_pos = pos + 1;
                pos = line.find("[", last_pos);
            }
        }
        else if(line_count > 10)
        {
            size_t pos = line.find(" from ");
            int num_of_containers = std::stoi(line.substr(5, pos-5));
            std::string from_stack_str(1, line[pos+6]);
            int from_stack = std::stoi(from_stack_str);

            std::string to_stack_str(1, line[pos+11]);
            int to_stack = std::stoi(to_stack_str);

            actions.push_back(std::vector<int>());
            actions.at(line_count-11).push_back(num_of_containers);
            actions.at(line_count-11).push_back(from_stack);
            actions.at(line_count-11).push_back(to_stack);
        }
        line_count++;
    }
    for(std::vector<char>& v: containers_v)
    {
        containers.push_back(construct_stack_from_vector<char>(v));
    }

    for(std::vector<int>& v: actions)
    {
        for(int i=0; i<v.at(0); i++)
        {
            int from_index = v.at(1) - 1;
            int to_index = v.at(2) - 1;
            containers.at(to_index).push(containers.at(from_index).top());
            containers.at(from_index).pop();
        }
    }

    std::cout << "part a: ";
    for(std::stack<char>& s: containers)
    {
        std::cout << s.top() << " ";
    }
    std::cout << std::endl;

    return -1;
}

int part_b()
{
    std::ifstream instream("input.txt");
    std::vector<std::vector<char>> containers_v(9);
    std::vector<std::vector<int>> actions;
    std::vector<std::stack<char>> containers;

    int line_count = 1;

    for(std::string line; getline(instream, line);)
    {
        if (line_count < 9)
        {
            size_t last_pos = 0;
            size_t pos = line.find("[", last_pos);
            while(pos != std::string::npos)
            {
                containers_v.at(pos/4).push_back(line[pos+1]);
                last_pos = pos + 1;
                pos = line.find("[", last_pos);
            }
        }
        else if(line_count > 10)
        {
            size_t pos = line.find(" from ");
            int num_of_containers = std::stoi(line.substr(5, pos-5));
            std::string from_stack_str(1, line[pos+6]);
            int from_stack = std::stoi(from_stack_str);

            std::string to_stack_str(1, line[pos+11]);
            int to_stack = std::stoi(to_stack_str);

            actions.push_back(std::vector<int>());
            actions.at(line_count-11).push_back(num_of_containers);
            actions.at(line_count-11).push_back(from_stack);
            actions.at(line_count-11).push_back(to_stack);
        }
        line_count++;
    }
    for(std::vector<char>& v: containers_v)
    {
        containers.push_back(construct_stack_from_vector<char>(v));
    }

    for(std::vector<int>& v: actions)
    {
        std::vector<int> s;
        int from_index = v.at(1) - 1;
        int to_index = v.at(2) - 1;

        for(int i=0; i<v.at(0); i++)
        {
            s.push_back(containers.at(from_index).top());
            containers.at(from_index).pop();
        }
        for(auto it=rbegin(s); it!=rend(s); it++)
        {
            containers.at(to_index).push(*it);
        }
    }

    std::cout << "part b: ";
    for(std::stack<char>& s: containers)
    {
        std::cout << s.top() << "";
    }
    std::cout << std::endl;

    return -1;
}

int main()
{
    part_a();
    part_b();
}
