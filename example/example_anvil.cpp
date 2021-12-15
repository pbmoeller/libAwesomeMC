#include <anvil/anvil_read.hpp>
#include <anvil/constants.hpp>
#include <nbt/nbt_print.hpp>

#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char **argv)
{
    std::string filename = R"(E:\Coding\Projects\Minecraft\libAwesomeMC\data\nbt\r.-1.-1.mca)";

    anvil::Region region = anvil::loadRegion(filename);

    std::ofstream stream(R"(E:\Coding\Projects\Minecraft\libAwesomeMC\data\nbt\r.-1.-1.mca.txt)");

    const anvil::RegionHeader &rHeader = region.getRegionHeader();
    for(unsigned int i = 0; i < anvil::ChunkCount; ++i) {
        if(rHeader.getChunkInfoAt(i).isEmpty()) {
            continue;
        }

        anvil::Chunk c = region.getChunkAt(i);
        stream << "\n\n----- " << i << " -----\n\n" << std::endl;
        stream << nbt::printNbtData(c.getRootTag(), true);
    }
    stream.close();

    return 0;
}