// AwesomeMC
#include <AwesomeMC/global.hpp>
#include <AwesomeMC/anvil/region.hpp>

// STL
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
    AMC_UNUSED(argc);
    AMC_UNUSED(argv);
    
    const std::string testFolderPath = "..\\..\\..\\test\\testdata\\world\\libAwesomeMC_TestWorld_1_18_1\\region\\";
    std::string filename = testFolderPath + "r.-1.-1.mca";
    amc::Region region;
    region.loadFromFile(filename);

    amc::Chunk &chunk = region.getChunkAt(0);
    amc::Block b = chunk.getBlockAt(3, 3, 3);


    amc::Block b2 = region.getBlockAt(-15, -16, -48);

    return 0;
}