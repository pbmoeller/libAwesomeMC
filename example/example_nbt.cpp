#include "nbt/tags.hpp"
#include "nbt/nbt_reader.hpp"
#include "util/compression.hpp"

// STL
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

int main(int agrc, char **argv)
{
    std::string file1 = R"(..\..\..\data\nbt\hello_world.nbt)";

    std::ifstream strm1(file1, std::ios::binary);
    if(!strm1.is_open()) {
        std::cerr << "Could not open file." << std::endl;
    } else {
        std::cout << "Opened NBT file: " << file1 << std::endl;

        strm1.seekg(0, std::ios::end);
        size_t size = strm1.tellg();
        std::vector<unsigned char> data(size, 0);
        strm1.seekg(0);
        strm1.read((char*)&data[0], size);

        nbt::AbstractTag *tag = nbt::NbtReader::readNbtData(data);

        std::cout << "\n===\n"
                  << nbt::NbtReader::printNbtData(tag)
                  << "===\n" << std::endl;
    }

    std::string file2 = R"(..\..\..\data\nbt\bigtest.nbt)";

    std::ifstream strm2(file2, std::ios::binary);
    if(!strm2.is_open()) {
        std::cerr << "Could not open file." << std::endl;
    } else {
        std::cout << "Opened NBT file: " << file2;

        strm2.seekg(0, std::ios::end);
        size_t size = strm2.tellg();
        std::vector<unsigned char> data(size, 0);
        strm2.seekg(0);
        strm2.read((char*)&data[0], size);

        bool ret = util::inflate_gzip(data);
        if(!ret) {
            std::cerr << "inflate_gzip error." << std::endl;
        }
        
        nbt::AbstractTag *tag = nbt::NbtReader::readNbtData(data);

        std::cout << "\n===\n" 
                  << nbt::NbtReader::printNbtData(tag)
                  << "===\n" << std::endl;
    }


    return 0;
}