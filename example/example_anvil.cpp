// AwesomeMC
#include <AwesomeMC/anvil/anvil_read.hpp>
#include <AwesomeMC/constants.hpp>
#include <AwesomeMC/nbt/nbt_print.hpp>

// STL
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
    std::string filename = R"(E:\Coding\Projects\Minecraft\libAwesomeMC\data\nbt\r.0.-1.mca)";

    amc::Region region = amc::loadRegion(filename);

    std::ofstream stream(R"(E:\Coding\Projects\Minecraft\libAwesomeMC\data\nbt\r.0.-1.mca.txt)");

    const amc::RegionHeader &rHeader = region.getRegionHeader();
    for(unsigned int i = 0; i < amc::ChunkCount; ++i) {
        if(rHeader.getChunkInfoAt(i).isEmpty()) {
            continue;
        }

        amc::Chunk c = region.getChunkAt(i);
        stream << "\n\n----- " << i << " -----\n\n" << std::endl;
        stream << amc::printNbtData(c.getRootTag(), true);
    }
    stream.close();

    return 0;
}