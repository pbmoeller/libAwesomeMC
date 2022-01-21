#include <AwesomeMC/nbt/nbt_read.hpp>

// AwesomeMC
#include <AwesomeMC/nbt/tags/tags.hpp>
#include <AwesomeMC/util/byte_stream.hpp>
#include <AwesomeMC/util/compression.hpp>

// STL
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

namespace nbt
{

std::vector<unsigned char> loadNbtData(const std::string &filename,
                                       bool isCompressed)
{
    // Open filestream
    std::ifstream stream(filename, std::ios::binary);

    if(!stream.is_open()) {
        throw std::runtime_error(std::string("Could not open file for reading: ").append(filename));
    } else {
        stream.seekg(0, std::ios::end);
        size_t size = stream.tellg();
        std::vector<unsigned char> data(size, 0);
        stream.seekg(0);
        stream.read((char*)&data[0], size);

        if(isCompressed) {
            bool ret = util::inflate_gzip(data);
            if(!ret) {
                throw std::runtime_error("Error: inflate_gzip failed.");
            }
        }

        return data;
    }
}

CompoundTag* readNbtData(const std::vector<unsigned char> &data)
{
    CompoundTag *root = nullptr;

    // Init the ByteStream object.
    util::ByteStream byteStream(data);
    byteStream.setSwap(util::ByteStream::Swap::SwapEndian);

    // The first tag must not be an EndTag, which means the CompoundTag must be empty.
    char type = readValue<char>(byteStream);
    if(type == static_cast<char>(TagType::End)) {
        return root;
    } else {
        // Get the name
        int16_t nameLength = readValue<int16_t>(byteStream);
        std::string name;
        if(!byteStream.readString(name, nameLength)) {
            throw std::runtime_error("Error reading name");
        }

        // The first tag should always be a compound tag.
        // So we expect to read sub tags from here on.
        root = new CompoundTag(name);
        AbstractTag *subTag = nullptr;

        // Keep reading sub tags as long there is no EndTag.
        do {
            subTag = readSubTag(byteStream, false, TagType::End);
            if(!subTag) {
                throw std::runtime_error("Failed to parse Sub Tag");
            }
            if(subTag->getType() != TagType::End) {
                root->pushBack(subTag);
            }
        } while(subTag->getType() != TagType::End);
        delete subTag;
    }

    return root;
}

AbstractTag* readSubTag(util::ByteStream &stream,
                        bool isListItem,
                        TagType listType)
{
    // Check if stream is good
    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream");
    }

    // Read tag header data
    TagType     type;
    std::string name;
    if(isListItem) {
        type = listType;
    } else {
        type = static_cast<TagType>(readValue<char>(stream));
        if(type != TagType::End) {
            int16_t nameLength = readValue<int16_t>(stream);
            if(!stream.readString(name, nameLength)) {
                throw std::runtime_error("Error reading name");
            }
        }
    }

    // Read data based on type
    AbstractTag *tag    = nullptr;
    AbstractTag *subTag = nullptr;
    switch(type) {
        case TagType::End:
            tag = new EndTag();
            break;
        case TagType::Byte:
            tag = new ByteTag(name, readValue<char>(stream));
            break;
        case TagType::Short:
            tag = new ShortTag(name, readValue<int16_t>(stream));
            break;
        case TagType::Int:
            tag = new IntTag(name, readValue<int32_t>(stream));
            break;
        case TagType::Long:
            tag = new LongTag(name, readValue<int64_t>(stream));
            break;
        case TagType::Float:
            tag = new FloatTag(name, readValue<float>(stream));
            break;
        case TagType::Double:
            tag = new DoubleTag(name, readValue<double>(stream));
            break;
        case TagType::ByteArray:
            tag = new ByteArrayTag(name, readArrayValues<int8_t>(stream));
            break;
        case TagType::String:
            tag = new StringTag(name, readStringValue(stream));
            break;
        case TagType::List:
        {
            TagType listTagType = static_cast<TagType>(readValue<char>(stream));
            int32_t listLength = readValue<int32_t>(stream);
            ListTag *listTag = new ListTag(name, listTagType);

            // Read the sub tags
            for(int i = 0; i < listLength; ++i) {
                subTag = readSubTag(stream, true, listTagType);
                listTag->pushBack(subTag);
            }
            tag = listTag;
            break;
        }
        case TagType::Compound:
        {
            // Read all sub tags
            CompoundTag *compTag = new CompoundTag(name);
            do {
                subTag = readSubTag(stream, false, TagType::End);
                if(!subTag) {
                    throw std::runtime_error("Failed to parse Sub Tag");
                }
                if(subTag->getType() != TagType::End) {
                    compTag->pushBack(subTag);
                }
            } while(subTag->getType() != TagType::End);
            tag = compTag;
            delete subTag;
            break;
        }
        case TagType::IntArray:
            tag = new IntArrayTag(name, readArrayValues<int32_t>(stream));
            break;
        case TagType::LongArray:
            tag = new LongArrayTag(name, readArrayValues<int64_t>(stream));
            break;
        default:
            throw std::runtime_error("Invalid tag type.");
    }

    return tag;
}

std::string readStringValue(util::ByteStream &stream)
{
    // Check if stream is good
    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream");
    }

    int16_t nameLength = readValue<int16_t>(stream);
    std::string name;
    if(!stream.readString(name, nameLength)) {
        throw std::runtime_error("Error reading name");
    }

    return name;
}

} // namespace nbt
