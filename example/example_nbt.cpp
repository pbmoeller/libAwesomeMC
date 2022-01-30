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
#if defined(_MSC_VER)
    std::string programName = "example_nbt.exe";
#elif defined(__GNUC__)
    std::string programName = "example_nbt";
#endif

    bool compressed = false;
    std::string file;
    std::string outputFile;

    if(argc < 2) {
        std::cout << "Usage: "
                  << programName << " FILENAME [OPTIONS]\n"
                  << "Prints the given nbt file to the console window.\n\n"
                  << "  -c               the nbt file is compressed.\n"
                  << "  -o=<filename>    the output is printed to a file rather\n"
                  << "                   than to the console window.\n\n"
                  << std::endl;

        file = R"(..\..\..\test\testdata\world\libAwesomeMC_TestWorld_1_18_1\level.dat)";
        compressed = true;

        std::cout << "Inputfile: " << file << "\n";
        std::cout << "Compression = true" << "\n" << std::endl;
    } else {
        file = argv[1];
        std::cout << "Inputfile: " << file << std::endl;
        for(int i = 2; i < argc; ++i) {
            std::string str(argv[i]);
            if(str.starts_with("-c")) {
                compressed = true;
                std::cout << "Compression = true" << std::endl;
            } else if(str.starts_with("-o")) {
                size_t pos = str.find('=');
                outputFile = str.substr(pos + 1);
                std::cout << "Outputfile: " << outputFile << std::endl;
            }
        }
        std::cout << "\n\n";
    }

    std::vector<unsigned char> data1 = nbt::loadNbtData(file, compressed);
    nbt::CompoundTag *tag1 = nbt::readNbtData(data1);

    if(outputFile.empty()) {
        std::cout << nbt::printNbtData(tag1)
                  << std::endl;
    } else {
        std::ofstream fstrm(outputFile);
        if(fstrm) {
            fstrm << nbt::printNbtData(tag1);
        }
    }

    return 0;
}