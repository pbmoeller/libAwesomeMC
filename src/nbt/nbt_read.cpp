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
#include <filesystem>

namespace amc
{

std::vector<unsigned char> fileReadAll(std::ifstream &strm)
{
    strm.seekg(0, std::ios::end);
    size_t size = strm.tellg();
    std::vector<unsigned char> data(size, 0);
    strm.seekg(0);
    strm.read((char*)&data[0], size);
    return data;
}

bool isNbtFile(const std::string &filename)
{
    // Open filestream
    std::ifstream file(filename, std::ios::binary);
    if(file.is_open()) {
        // Load first 2 bytes to check file header
        std::vector<unsigned char> data(2, 0);
        file.read((char*)&data[0], 2);
        if(!file) {
            return false;
        }
        bool isCompressed = isGzipCompressed(data);
        file.seekg(0);

        // If the file is compressed, load it completely
        if(isCompressed) {
            data = fileReadAll(file);
            bool ret = inflate_gzip(data);
            if(!ret) {
                return false;
            }
        }

        // Check the first byte in the data. It must be a CompoundTag type
        if(data[0] == static_cast<unsigned char>(TagType::Compound)) {
            return true;
        }
    }
    return false;
}

std::vector<unsigned char> loadNbtData(const std::string &filename,
                                       bool isCompressed)
{
    // Open filestream
    std::ifstream stream(filename, std::ios::binary);

    if(!stream.is_open()) {
        throw std::runtime_error(std::string("Could not open file for reading: \"").append(filename).append("\"!"));
    } else {
        std::vector<unsigned char> data = fileReadAll(stream);

        if(isCompressed) {
            bool ret = inflate_gzip(data);
            if(!ret) {
                throw std::runtime_error("Error: inflate_gzip failed.");
            }
        }

        return data;
    }
}

std::unique_ptr<CompoundTag> readNbtFile(const std::string &filename)
{
    CompressionType compressionType;
    return readNbtFile(filename, compressionType);
}

std::unique_ptr<CompoundTag> readNbtFile(const std::string &filename, CompressionType &compressionType)
{
    // Check if file exists
    if(!std::filesystem::exists(filename)) {
        return std::unique_ptr<CompoundTag>();
    }

    // Open filestream
    std::ifstream file(filename, std::ios::binary);
    if(file.is_open()) {
        // Check if file is compressed and which compression is used
        // Load first 2 bytes to check file header
        std::vector<unsigned char> data(2, 0);
        file.read((char*)&data[0], 2);
        if(!file) {
            return std::unique_ptr<CompoundTag>();
        }
        compressionType = getCompression(data);
        file.seekg(0);

        // Read all data from file
        // If the file is compressed do also uncompression
        bool ret = true;
        data = fileReadAll(file);
        if(compressionType == CompressionType::GZip) {
            ret = inflate_gzip(data);
        } else if(compressionType == CompressionType::Zlib) {
            ret = inflate_zlib(data);
        }

        // If any error occured return empty CompoundTag
        if(!ret) {
            return std::unique_ptr<CompoundTag>();
        }

        // Check the first byte in the data. It must be a CompoundTag type
        if(data[0] != static_cast<unsigned char>(TagType::Compound)) {
            return std::unique_ptr<CompoundTag>();
        }

        return readNbtData(data);
    }
    
    return std::unique_ptr<CompoundTag>();
}

std::unique_ptr<CompoundTag> readNbtData(const std::vector<unsigned char> &data)
{
    // Init the ByteStream object.
    ByteStream byteStream(data);
    byteStream.setSwap(ByteStream::Swap::SwapEndian);

    // The first tag must not be an EndTag or an invalid (Unknown) tag, which means the CompoundTag must be empty.
    // TODO: Check!! => In fact the first Tag must be a CompoundTag by definition.
    unsigned char type = readValue<unsigned char>(byteStream);
    if(type == static_cast<unsigned char>(TagType::Unknown)) {
        throw std::runtime_error("Invalid tag type.");
    } else if(type == static_cast<unsigned char>(TagType::End)) {
        return std::unique_ptr<CompoundTag>(nullptr);
    } else {
        // Get the name
        std::string name = readStringValue(byteStream);

        // The first tag always is a CompoundTag.
        // So we expect to read child tags from here on.
        std::unique_ptr<CompoundTag> root = std::make_unique<CompoundTag>(name);
        AbstractTag *childTag = nullptr;

        // Keep reading sub tags as long there is no EndTag.
        do {
            childTag = readChildTag(byteStream, false, TagType::End);
            if(!childTag) {
                throw std::runtime_error("Failed to read child tag.");
            }
            if(childTag->getType() != TagType::End) {
                root->pushBack(childTag);
            }
        } while(childTag->getType() != TagType::End);
        delete childTag;
    
        return root;
    }
}

AbstractTag* readChildTag(ByteStream &stream,
                          bool isListItem,
                          TagType listType)
{
    // Check if stream is good
    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream.");
    }

    // Read tag header data if tag is not a list item
    TagType     type;
    std::string name;
    if(isListItem) {
        type = listType;
    } else {
        type = static_cast<TagType>(readValue<unsigned char>(stream));
        if(type != TagType::End) {
            name = readStringValue(stream);
        }
    }

    // Read data based on type
    AbstractTag *tag        = nullptr;
    AbstractTag *childTag   = nullptr;
    switch(type) {
        case TagType::End:
            tag = new EndTag();
            break;
        case TagType::Byte:
            tag = new ByteTag(name, readValue<int8_t>(stream));
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
            TagType listTagType = static_cast<TagType>(readValue<unsigned char>(stream));
            ListTag *listTag    = new ListTag(name, listTagType);

            // Read the sub tags
            int32_t listLength  = readValue<int32_t>(stream);
            for(int i = 0; i < listLength; ++i) {
                childTag = readChildTag(stream, true, listTagType);
                listTag->pushBack(childTag);
            }
            tag = listTag;
            break;
        }
        case TagType::Compound:
        {
            // Read all sub tags
            CompoundTag *compoundTag = new CompoundTag(name);
            do {
                childTag = readChildTag(stream, false, TagType::End);
                if(!childTag) {
                    throw std::runtime_error("Failed to parse child tag.");
                }
                if(childTag->getType() != TagType::End) {
                    compoundTag->pushBack(childTag);
                }
            } while(childTag->getType() != TagType::End);
            tag = compoundTag;
            delete childTag;
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

std::string readStringValue(ByteStream &stream)
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

} // namespace amc
