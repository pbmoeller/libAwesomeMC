#include <iostream>

#include <zlib.h>

int main(int argc, char **argv)
{
    std::cout << "Example 1: Reading Anvil File" << std::endl;

    if(argc != 2) {
        std::cerr << "Usage: example1 <path-to-anvil-file>" << std::endl;
        return 1;
    } else {
        try {
            std::cout << "Reading Anvil Map File: " << argv[1] << std::endl;

        } catch(std::runtime_error &ex) {
            std::cerr << "Runtime Error: " << ex.what() << std::endl;
            return 1;
        } catch(...) {
            std::cerr << "Any other exception occured." << std::endl;
            return 1;
        }
    }

    std::cout << zlibVersion() << std::endl;

    return 0;
}