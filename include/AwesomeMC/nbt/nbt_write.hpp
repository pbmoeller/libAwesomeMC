#ifndef AWESOME_NBT_NBT_WRITE_HPP
#define AWESOME_NBT_NBT_WRITE_HPP

// AwesomeMC
#include <AwesomeMC/util/compression.hpp>

// STL
#include <string>

namespace amc
{

class CompoundTag;

bool writeNbtFile(const std::string &filename, 
                  CompoundTag *tag, 
                  CompressionType compression = CompressionType::GZip);

} // namespace nbt

#endif // AWESOME_NBT_NBT_WRITE_HPP