#ifndef AWESOME_NBT_NBT_WRITE_HPP
#define AWESOME_NBT_NBT_WRITE_HPP

// STL
#include <string>

namespace amc
{

class CompoundTag;

bool writeNbtFile(const std::string &filename, CompoundTag *tag, bool compress = true);

} // namespace nbt

#endif // AWESOME_NBT_NBT_WRITE_HPP