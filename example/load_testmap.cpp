// AwesomeMC
#include <AwesomeMC/anvil/anvil_read.hpp>
#include <AwesomeMC/global.hpp>

// STL
#include <iostream>
#include <string>
#include <fstream>

const std::string testFolder = "..\\..\\..\\test\\testdata\\world\\";

int main(int argc, char **argv)
{
    AMC_UNUSED(argc);
    AMC_UNUSED(argv);

    std::string filename = testFolder + "libAwesomeMC_TestWorld_1_18_1\\region\\r.-1.-1.mca";
    amc::Region region = amc::loadRegion(filename);

    amc::Block b = region.getBlockAt(-15, -16, -48);

    return 0;
}