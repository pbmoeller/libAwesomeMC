// AwesomeMC
#include <AwesomeMC/nbt/nbt_write.hpp>
#include <AwesomeMC/nbt/tags/tags.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <fstream>
#include <vector>

namespace amc
{

bool writeNbtFile(const std::string &filename, CompoundTag *tag, bool compress)
{
    // Get data from tag
    std::vector<unsigned char> data = tag->getData(false);

    if(compress) {
        bool ret = deflate_gzip(data);
        if(!ret) {
            return false;
        }
    }

    // Open filestream
    std::ofstream stream(filename, std::ios::binary);
    if(!stream.is_open()) {
        throw std::runtime_error(std::string("Could not open file for writing:").append(filename));
    } else {
        stream.write((char*)data.data(), data.size());
        return true;
    }
}

} // namespace nbt