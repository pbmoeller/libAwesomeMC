// AwesomeMC
#include <AwesomeMC/nbt/tags/tags.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/nbt/nbt_print.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
    bool compressed = false;
    std::string file;;

    if(argc < 3) {
        std::cout << "Usage: "
                  << "example_nbt.exe <filename> <compressed>\n"
                  << "\t filename : path"
                  << "\t compressed : [1 | 0]" << std::endl;

        file = R"(..\..\..\test\testdata\world\libAwesomeMC_TestWorld_1_18_1\level.dat)";
        compressed = true;
    } else {
        file = argv[1];
        std::cout << argv[1] << std::endl;
        std::cout << argv[2] << std::endl;
        compressed = (std::atoi(argv[2]) == 1);
    }

    std::vector<unsigned char> data1 = nbt::loadNbtData(file, compressed);
    nbt::AbstractTag *tag1 = nbt::readNbtData(data1);

    std::cout << "\n===\n"
        << nbt::printNbtData(tag1)
        << "===\n" << std::endl;

    return 0;
}