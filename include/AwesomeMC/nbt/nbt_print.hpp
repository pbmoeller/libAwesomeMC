#ifndef AWESOMEMC_NBT_NBT_PRINT_HPP
#define AWESOMEMC_NBT_NBT_PRINT_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/tags.hpp>

// STL
#include <sstream>

namespace nbt
{

class AbstractTag;

std::string printNbtData(const AbstractTag *root,
                         bool printArrayContent = false);

void printNextNbtDataLevel(const AbstractTag *tag,
                           std::stringstream &sstr,
                           int indent,
                           bool printArrayContent = false);

std::string getTagName(TagType type);

template<typename T>
void printSimpleDataType(const T *tag,
                         std::stringstream &sstr,
                         int indent)
{
    sstr << std::string(indent, ' ') << getTagName(tag->getType())
         << "(\"" << tag->getName() << "\"): " << (int64_t)tag->getValue() << "\n";
}

} // namespace nbt

#endif // AWESOMEMC_NBT_NBT_PRINT_HPP