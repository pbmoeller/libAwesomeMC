// AwesomeMC
#include <AwesomeMC/nbt/tags/tags.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/nbt/nbt_print.hpp>
#include <AwesomeMC/nbt/nbt_read.hpp>
#include <AwesomeMC/util/compression.hpp>
#include <AwesomeMC/version.hpp>

// STL
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>

#if defined(_MSC_VER)
std::string g_programName = "example_nbt.exe";
#elif defined(__GNUC__)
std::string g_programName = "example_nbt";
#endif

void printUsage()
{
    std::cout << "Usage: "
        << g_programName << " FILENAME [OPTIONS]\n"
        << "Prints the given nbt file to the console window.\n\n"
        << "  -c               the nbt file is compressed.\n"
        << "  -o=<filename>    the output is printed to a file rather\n"
        << "                   than to the console window.\n"
        << "  -h, --help       print this help message\n"
        << "  -v, --version    print library version\n"
        << std::endl;
}

int main(int argc, char **argv)
{
    bool compressed = false;
    std::string file;
    std::string outputFile;

    if(argc < 2) {
        // No valid parameters given, print usage and run example.
        printUsage();

        file = R"(../../../test/testdata/world/libAwesomeMC_TestWorld_1_18_1/level.dat)";
        compressed = true;

        std::cout << "Inputfile: " << file << "\n";
        std::cout << "Compression = true" << "\n" << std::endl;
    } else if(argc == 2) {
        // Check single parameters
        std::string arg = argv[1];
        if(arg == "-v" || arg == "--version") {
            std::cout << "AwesomeMC Version: " << AwesomeMC_Version 
                      << "-" << AwesomeMC_GitHash 
                      << "(" << AwesomeMC_GitBranch << ")" << std::endl;
            return 0;
        } else if(arg == "-h" || arg == "--help") {
            printUsage();
            return 0;
        }

        // If the parameter is invalid, print a message and usage information.
        std::cout << "Invalid argument: " << arg << std::endl;
        printUsage();
        return 0;

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

    // Use try catch, since we use user input that might be wrong.
    try {
        // Load and uncompress NBT data from file into data buffer. 
        std::vector<unsigned char> data1 = amc::loadNbtData(file, compressed);

        // Read NBT data from data buffer.
        amc::CompoundTag *tag1 = nullptr;
        tag1 = amc::readNbtData(data1);

        // Check if the NBT data should be printed to console or a given output file.
        if(outputFile.empty()) {
            std::cout << amc::printNbtData(tag1)
                      << std::endl;
        } else {
            std::ofstream fstrm(outputFile);
            if(fstrm) {
                fstrm << amc::printNbtData(tag1);
            }
        }

    } catch(std::exception &e) {
        std::cout << "Failed to read and print NBT data.\nException: " << e.what() << std::endl;
    }

    return 0;
}