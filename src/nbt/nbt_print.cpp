#include "nbt/nbt_print.hpp"
#include "nbt/tags/tags.hpp"

// STL
#include <string>
#include <iomanip>
#include <sstream>

namespace nbt
{

std::string printNbtData(const AbstractTag *root,
                         bool printArrayContent)
{
    std::stringstream sstr;

    if(root->getType() != TagType::End) {
        printNextNbtDataLevel(root, sstr, 0, printArrayContent);
    }

    return sstr.str();
}

void printNextNbtDataLevel(const AbstractTag *tag,
                           std::stringstream &sstr,
                           int indent,
                           bool printArrayContent)
{
    switch(tag->getType())
    {
        case TagType::End:
        {
            break;
        }
        case TagType::Byte:
        {
            const ByteTag *t = static_cast<const ByteTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Byte) 
                 << "(\"" << t->getName() << "\"): " << (int)t->getValue() << "\n";
            break;
        }
        case TagType::Short:
        {
            const ShortTag *t = static_cast<const ShortTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Short)
                 << "(\"" << t->getName() << "\"): " << (int)t->getValue() << "\n";
            break;
        }
        case TagType::Int:
        {
            const IntTag *t = static_cast<const IntTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Int)
                 << "(\"" << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::Long:
        {
            const LongTag *t = static_cast<const LongTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Long)
                 << "(\"" << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::Float:
        {
            const FloatTag *t = static_cast<const FloatTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Float)
                 << "(\"" << t->getName() << "\"): " << std::setprecision(8) << t->getValue() << "\n";
            break;
        }
        case TagType::Double:
        {
            const DoubleTag *t = static_cast<const DoubleTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Double)
                 << "(\"" << t->getName() << "\"): " << std::setprecision(16) << t->getValue() << "\n";
            break;
        }
        case TagType::ByteArray:
        {
            const ByteArrayTag *t = static_cast<const ByteArrayTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::ByteArray)
                 << "(\"" << t->getName() << "\"):";
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
            const StringTag *t = static_cast<const StringTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::String)
                 << "(\"" << t->getName() << "\"): " << t->getValue() << "\n";
            break;
        }
        case TagType::List:
        {
            const ListTag *t = static_cast<const ListTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::List)
                 << "(\"" << t->getName() << "\"): " << t->size() << " entries of type " << getTagName(t->getListType()) << "\n";
            sstr << std::string(indent, ' ') << "{\n";
            for(const AbstractTag *tag : t->getValue()) {
                printNextNbtDataLevel(tag, sstr, indent + 2);
            }
            sstr << std::string(indent, ' ') << "}\n";
            break;
        }
        case TagType::Compound:
        {
            const CompoundTag *t = static_cast<const CompoundTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::Compound)
                 << "(\"" << t->getName() << "\"): " << t->size() << " entries\n";
            sstr << std::string(indent, ' ') << "{\n";
            for(size_t i = 0; i < t->size(); ++i) {
                printNextNbtDataLevel(t->at(i), sstr, indent + 2);
            }
            sstr << std::string(indent, ' ') << "}\n";
            break;
        }
        case TagType::IntArray:
        {
            const IntArrayTag *t = static_cast<const IntArrayTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::IntArray)
                 << "(\"" << t->getName() << "\"): ";
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
            const LongArrayTag *t = static_cast<const LongArrayTag*>(tag);
            sstr << std::string(indent, ' ') << getTagName(TagType::LongArray)
                 << "(\"" << t->getName() << "\"): " << t->size() << " entries\n";
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

std::string getTagName(TagType type)
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

} // namespace nbt