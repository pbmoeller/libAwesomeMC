#include "nbt/nbt_reader.hpp"
#include "nbt/tags.hpp"
#include "util/byte_stream.hpp"

// STL
#include <sstream>
#include <iomanip>

namespace nbt
{

AbstractTag* NbtReader::readNbtData(const std::vector<unsigned char> &data)
{
    CompoundTag *root = nullptr;

    // Inii the ByteStream object.
    util::ByteStream byteStream(data);
    byteStream.setSwap(util::ByteStream::Swap::SwapEndian);

    // The first tag must not be an end tag, which means the compound tag must be empty.
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

        // Keep reading sub tags as long there is no end tag.
        do {
            subTag = readSubTag(byteStream, false, TagType::End);
            if(!subTag) {
                throw std::runtime_error("Failed to parse Sub Tag");
            }
            if(subTag->getType() != TagType::End) {
                root->pushBack(subTag);
            }
        } while(subTag->getType() != TagType::End);
    }

    return root;
}

AbstractTag* NbtReader::readSubTag(util::ByteStream &stream,
                                   bool isListItem,
                                   TagType listType)
{
    // Check if stream is good
    if(!stream.good()) {
        throw std::runtime_error("Unexpected end of stream");
    }

    // read tag header data
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

    // read data based on type
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
            tag = new ByteArrayTag(name, readArrayValues<char>(stream));
            break;
        case TagType::String:
            tag = new StringTag(name, readStringValue(stream));
            break;
        case TagType::List:
        {
            TagType type        = static_cast<TagType>(readValue<char>(stream));
            int32_t listLength  = readValue<int32_t>(stream);
            ListTag *listTag    = new ListTag(name, type);
            
            // read the sub tags
            for(int i = 0; i < listLength; ++i) {
                subTag = readSubTag(stream, true, type);
                listTag->pushBack(subTag);
            }
            tag = listTag;
            break;
        }
        case TagType::Compound:
        {
            // parse sub tags
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

std::string NbtReader::printNbtData(const AbstractTag *root, bool printArrayContent)
{
    std::stringstream sstr;
    
    if(root->getType() != TagType::End) {
        printNextNbtDataLevel(root, sstr, 0, printArrayContent);
    }

    return sstr.str();
}

void NbtReader::printNextNbtDataLevel(const AbstractTag *tag,
                                      std::stringstream &sstr,
                                      int indent,
                                      bool printArrayContent)
{
    switch(tag->getType())
    {
        case TagType::End:
            break;
        case TagType::Byte:
        {
            ByteTag *t = (ByteTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Byte(\""
                 << t->getName() << "\"): " << (int)t->getValue() << "\n";
            break;
        }
        case TagType::Short:
        {
            ShortTag *t = (ShortTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Short(\""
                 << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::Int:
        {
            IntTag *t = (IntTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Int(\""
                 << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::Long:
        {
            LongTag *t = (LongTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Long(\""
                 << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::Float:
        {
            FloatTag *t = (FloatTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Float(\""
                 << t->getName() << "\"): " << std::setprecision(8) << t->getValue() << "\n";
            break;
        }
        case TagType::Double:
        {
            DoubleTag *t = (DoubleTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Double(\""
                 << t->getName() << "\"): " << std::setprecision(16) << t->getValue() << "\n";
            break;
        }
        case TagType::ByteArray:
        {
            ByteArrayTag *t = (ByteArrayTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_ByteArray(\""
                 << t->getName() << "\"):";
            if(printArrayContent) {
                sstr << "\n" << std::string(indent, ' ') << "{\n";
                size_t i = 0;
                for(i = 0; i < t->size() - 1; ++i) {
                    sstr << " " << (int)t->at(i) << ",";
                }
                sstr << " " << (int)t->at(i) << "\n";
                sstr << std::string(indent, ' ') << "}\n";
            } else {
                sstr << " [" << t->size() << " bytes]\n";
            }
            break;
        }
        case TagType::String:
        {
            StringTag *t = (StringTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_String(\""
                 << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::List:
        {
            ListTag *t = (ListTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_List(\""
                 << t->getName() << "\"): " << t->size() << " entries of type " << getTypeName(t->getListType()) << "\n";
            sstr << std::string(indent, ' ') << "{\n";
            for(const AbstractTag *tag : t->getValue()) {
                printNextNbtDataLevel(tag, sstr, indent + 2);
            }
            sstr << std::string(indent, ' ') << "}\n";
            break;
        }
        case TagType::Compound:
        {
            CompoundTag *t = (CompoundTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_Compound(\""
                 << t->getName() << "\"): " << t->size() << " entries\n";
            sstr << std::string(indent, ' ') << "{\n";
            for(size_t i = 0; i < t->size(); ++i) {
                printNextNbtDataLevel(t->at(i), sstr, indent + 2);
            }
            sstr << std::string(indent, ' ') << "}\n";
            break;
        }
        case TagType::IntArray:
        {
            IntArrayTag *t = (IntArrayTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_IntArray(\""
                 << t->getName() << "\"): ";
            if(printArrayContent) {
                sstr << "\n" << std::string(indent, ' ') << "{\n";
                size_t i = 0;
                for(i = 0; i < t->size() - 1; ++i) {
                    sstr << " " << (int)t->at(i) << ",";
                }
                sstr << " " << (int)t->at(i) << "\n";
                sstr << std::string(indent, ' ') << "}\n";
            } else {
                sstr << " [" << t->size() * 2 << " bytes]\n";
            }
            break;
        }
        case TagType::LongArray:
        {
            LongArrayTag *t = (LongArrayTag*)(tag);
            sstr << std::string(indent, ' ') << "TAG_LongArray(\"" 
                 << t->getName() << "\"): " << t->size() << " entries\n";
            if(printArrayContent) {
                sstr << "\n" << std::string(indent, ' ') << "{\n";
                size_t i = 0;
                for(i = 0; i < t->size() - 1; ++i) {
                    sstr << " " << (int)t->at(i) << ",";
                }
                sstr << " " << (int)t->at(i) << "\n";
                sstr << std::string(indent, ' ') << "}\n";
            } else {
                sstr << " [" << t->size() * 4 << " bytes]\n";
            }
            break;
        }
        default:
            break;
    }
}

std::string NbtReader::readStringValue(util::ByteStream &stream)
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

std::string NbtReader::getTypeName(TagType type)
{
    switch(type)
    {
        case TagType::End:
            return "TAG_End";
        case TagType::Byte:
            return "TAG_Byte";
        case TagType::Short:
            return "TAG_Short";
        case TagType::Int:
            return "TAG_Int";
        case TagType::Long:
            return "TAG_Long";
        case TagType::Float:
            return "TAG_Float";
        case TagType::Double:
            return "TAG_Double";
        case TagType::ByteArray:
            return "TAG_ByteArray";
        case TagType::String:
            return "TAG_String";
        case TagType::List:
            return "TAG_List";
        case TagType::Compound:
            return "TAG_Compound";
        case TagType::IntArray:
            return "TAG_IntArray";
        case TagType::LongArray:
            return "TAG_LongArray";
        default:
            return "InvalidTag";
    }
}

} // namespace std
