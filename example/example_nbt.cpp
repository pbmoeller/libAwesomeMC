#include "nbt/tags.hpp"
#include "nbt/nbt_read.hpp"
#include "nbt/nbt_print.hpp"
#include "nbt/nbt_read.hpp"
#include "util/compression.hpp"

// STL
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

int main(int agrc, char **argv)
{
    std::string file1 = R"(..\..\..\data\nbt\hello_world.nbt)";
    std::vector<unsigned char> data1 = nbt::loadNbtData(file1, false);
    nbt::AbstractTag *tag1 = nbt::readNbtData(data1);

    std::cout << "\n===\n"
        << nbt::printNbtData(tag1)
        << "===\n" << std::endl;


    std::string file2 = R"(..\..\..\data\nbt\bigtest.nbt)";
    std::vector<unsigned char> data2 = nbt::loadNbtData(file2, true);
    nbt::AbstractTag *tag2 = nbt::readNbtData(data2);

    std::cout << "\n===\n"
        << nbt::printNbtData(tag2)
        << "===\n" << std::endl;

    return 0;
}