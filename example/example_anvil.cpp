// AwesomeMC
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/util/conversion.hpp>
#include <AwesomeMC/global.hpp>
#include <AwesomeMC/nbt/nbt_print.hpp>
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
    std::string filenameSave = testFolderPath + "tmp\\r.-1.-1.mca";

    amc::Region region;
    region.loadFromFile(filename);

    // Save Region to new file
    region.saveToFile(filenameSave);

    // print data of Chunk 31, 31
    std::ofstream stream(testFolderPath + "tmp\\r.-1.-1.mca_chunk_31_31.txt");
    const int index = amc::chunkIndexFromXZ(31, 31);
    if(!region.getChunkAt(index).isEmpty()) {
        amc::Chunk c = region.getChunkAt(index);
        stream << amc::printNbtData(c.getRootTag(), true);
    }
    stream.close();

    return 0;
}

