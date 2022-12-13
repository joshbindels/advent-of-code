if [ -z "$1" ]
  then
    echo "No argument provided"
    exit -1
fi

mkdir $1
touch $1/main.cpp
touch $1/input.txt
touch $1/CMakeLists.txt

echo "
#include <iostream>
#include <fstream>

void part_a()
{
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
" >> $1/main.cpp

echo "add_subdirectory($1)" >> CMakeLists.txt

echo "
add_executable($1_22 main.cpp)
target_link_libraries($1_22 PUBLIC readlines)

file(COPY \${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION \${CMAKE_CURRENT_BINARY_DIR})" >> $1/CMakeLists.txt

