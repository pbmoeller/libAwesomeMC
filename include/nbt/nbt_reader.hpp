#ifndef NBT_NBT_READER_HPP
#define NBT_NBT_READER_HPP

// nbt
#include "nbt/tags/abstract_tag.hpp"
#include "util/byte_stream.hpp"

// STL
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

namespace nbt
{

class AbstractTag;
class CompoundTag;

class NbtReader
{
public:
    static AbstractTag* readNbtData(const std::vector<unsigned char> &data);
    static AbstractTag* readSubTag(util::ByteStream &stream, 
                                   bool isListItem, 
                                   TagType listType);

    static std::string printNbtData(const AbstractTag *root, bool printArrayContent = false);

private:
    static void printNextNbtDataLevel(const AbstractTag *tag, 
                                      std::stringstream &sstr,
                                      int indent,
                                      bool printArrayContent = false);

    template<typename T>
    static T readValue(util::ByteStream &stream)
    {
        T value;

        if(!stream.good()) {
            throw std::runtime_error("Unexpected end of stream");
        }

        stream >> value;
        return value;
    }

    template<typename T>
    static std::vector<T> readArrayValues(util::ByteStream &stream)
    {
        std::vector<T> values;

        if(!stream.good()) {
            throw std::runtime_error("Unexpected end of stream");
        }

        int32_t arrayLength = readValue<int32_t>(stream);
        values.resize(arrayLength);
        for(int32_t i = 0; i < arrayLength; ++i) {
            values[i] = readValue<T>(stream);
        }
        return values;
    }

    static std::string readStringValue(util::ByteStream &stream);

    static std::string getTypeName(TagType type);
};

} // namespace nbt

#endif // NBT_NBT_READER_HPP