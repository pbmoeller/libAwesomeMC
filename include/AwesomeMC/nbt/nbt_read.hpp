#ifndef AWESOMEMC_NBT_NBT_READ_HPP
#define AWESOMEMC_NBT_NBT_READ_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/abstract_tag.hpp>
#include <AwesomeMC/util/byte_stream.hpp>

// STL
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>

namespace amc
{

class AbstractTag;
class CompoundTag;

bool isNbtFile(const std::string &filename);

std::vector<unsigned char> loadNbtData(const std::string &filename, 
                                       bool isCompressed);

std::unique_ptr<CompoundTag> readNbtFile(const std::string &filename);
std::unique_ptr<CompoundTag> readNbtData(const std::vector<unsigned char> &data);
AbstractTag* readChildTag(ByteStream &stream, 
                        bool isListItem, 
                        TagType listType);

template<typename T>
T readValue(ByteStream &stream)
{
    T value;

    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream.");
    }

    stream >> value;
    return value;
}

template<typename T>
std::vector<T> readArrayValues(ByteStream &stream)
{
    std::vector<T> values;

    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream.");
    }

    int32_t arrayLength = readValue<int32_t>(stream);
    values.resize(arrayLength);
    for(int32_t i = 0; i < arrayLength; ++i) {
        values[i] = readValue<T>(stream);
    }
    return values;
}

std::string readStringValue(ByteStream &stream);

} // namespace amc

#endif // AWESOMEMC_NBT_NBT_READ_HPP