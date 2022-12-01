#include <iostream>
#include <readlines.hpp>

#define NUM_OF_BITS 12

int part_a()
{
    std::vector<int> input;

    common::get_lines_from_file("input.txt", input);

    int counter[NUM_OF_BITS] = {0};
    for (int& num: input)
    {
        int cur_num = num;
        for(int i=NUM_OF_BITS-1; i>=0; i--)
        {
            counter[i] += (cur_num & 1);
            cur_num >>= 1;
        }
    }

    int gam = 0;
    int eps = 0;
    size_t num_of_inputs = input.size();

    for (int i=0; i<NUM_OF_BITS; i++)
    {
        if (counter[i] > (num_of_inputs/2))
        {
            gam |= 1;
        }
        gam <<= 1;
    }
	gam >>= 1;

    for(int i=0; i<NUM_OF_BITS; i++)
    {
		eps <<= 1;
		eps |= (gam & (1 << (NUM_OF_BITS-i-1))) > 0 ? 0 : 1;
    }


    return gam * eps;
}

int main()
{
    std::cout << "Part A: " << part_a() << std::endl;
    return 0;
}
